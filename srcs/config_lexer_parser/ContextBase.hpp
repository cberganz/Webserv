/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextBase.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/18 02:37:44 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXTBASE_HPP
# define CONTEXTBASE_HPP

# include <string>
# include <vector>
# include <map>
# include "ParserConfig.hpp"
# include "tools.hpp"

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

class ContextBase : public ParserConfig {

public:
	typedef std::vector<std::string>			tokensContainer;
	typedef tokensContainer::iterator			tokensIterator;
	typedef std::map<std::string, std::string>	directivesContainer;
	typedef directivesContainer::iterator		directivesIterator;

	ContextBase();
	ContextBase(const ContextBase &src);
	ContextBase(tokensContainer &tokens);
	ContextBase(const std::string &contextName,
				const std::string &parentName);
	virtual ~ContextBase();

	ContextBase &operator=(const ContextBase &rhs);

protected:
	static tokensIterator tokensIt;

	void handleBlocOpening();
	void handleBlocEnding();

	void directiveReplaceInserter(directivesContainer &container);
	void copyParentDirectives(directivesContainer &parentContainer,
							  directivesContainer &container);

	class ParsingErrorException : public std::exception
    {
	private:
		const std::string message;

    public:
		ParsingErrorException(const std::string &contextName,
							  const char *errorDetails, 
							  const std::string &token);
		~ParsingErrorException() throw();

        const char* what() const throw();
    };

	void throwException(const char *errorDetails,
						const std::string &token) const;

}; // class ContextBase

#endif // CONTEXTBASE_HPP
