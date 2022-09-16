/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextBase.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 17:21:16 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXTBASE_HPP
# define CONTEXTBASE_HPP

# include <utility>
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>
# include "ParserConfig.hpp"
# include "tools.hpp"

class ContextBase : public ParserConfig {

public:
	typedef std::vector<std::string>			tokensContainer;
	typedef tokensContainer::iterator			tokensIterator;
	typedef std::map<std::string, std::string>	directivesContainer;
	typedef directivesContainer::iterator		directivesIterator;

	ContextBase();
	ContextBase(const ContextBase &src);
	ContextBase(tokensContainer &tokens);
	ContextBase(const std::string &contextName, const std::string &parentName);
	virtual ~ContextBase();

	ContextBase &operator=(const ContextBase &rhs);

protected:
	static tokensIterator tokensIt;

	void jumpBlocOpening();
	void jumpBlocEnding();

	void directiveReplaceInserter(directivesContainer &container);
	void directiveInserter(directivesContainer &container, directivesIterator &it);

	class ParsingErrorException : public std::exception
    {
	private:
		const std::string message;

    public:
		ParsingErrorException(const std::string &contextName, const char *errorDetails, const std::string &token);
		~ParsingErrorException() throw();

        const char* what() const throw();
    };

};

#endif
