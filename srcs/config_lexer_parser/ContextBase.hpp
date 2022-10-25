/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextBase.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/25 19:59:42 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXTBASE_HPP
# define CONTEXTBASE_HPP

# include <string>
# include <vector>
# include <map>
# include <utility>
# include "ParserConfig.hpp"
# include "../tools/utility.hpp"

# define BLOC_START "{"
# define BLOC_END "}"
# define DIRECTIVE_END ";"

/*
**	@brief The purpose of this class is to make abstraction of the Context class
**		   inherent complexity. It implements low level methods and manipulates
**		   iterators through tokens and other containers to demystify the Conte-
**		   -xt class implementation and allow easier code implementation and re-
**		   implementation.
**	@category class
*/

class Context;

class ContextBase : public ParserConfig {

public:
	typedef std::vector<std::string>							tokensContainer;
	typedef tokensContainer::const_iterator						tokensIterator;
	typedef std::map<std::string, std::vector<std::string> >	directivesContainer;
	typedef directivesContainer::iterator						directivesIterator;
	typedef directivesContainer::const_iterator					directivesConstIterator;

	ContextBase();
	ContextBase(const ContextBase &src);
	ContextBase(const tokensContainer &tokens);
	ContextBase(const std::string &contextName,
				const std::string &parentName);
	virtual ~ContextBase();

	ContextBase &operator=(const ContextBase &rhs);

	void copyParentDirectives(directivesContainer &parentContainer,
							  directivesContainer &container);

protected:
	static int m_fileLine;

	const std::string &getCurrentToken();
	const std::string &getFollowingToken(const int &offset);

	void handleBlocOpening();
	void handleBlocEnding();
	void handleNewline();
	void directiveInserter(directivesContainer &container);
	void insertDefaultIfExistingOrThrowException(directivesContainer &container,
												 const int &index);

	const std::string getKeyIdentifier();

	class ParsingErrorException : public std::exception
    {
	private:
		const std::string message;

    public:
		ParsingErrorException(const std::string &contextName,
							  const char *errorDetails, 
							  const std::string &token,
							  const int &fileLine);
		~ParsingErrorException() throw();

        const char* what() const throw();
    };

	void throwException(const char *errorDetails,
						const std::string &token) const;

private:
	static tokensIterator tokensIt;

}; // class ContextBase

#endif // CONTEXTBASE_HPP
