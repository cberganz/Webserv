/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContext.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 00:44:37 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACONTEXT_HPP
# define ACONTEXT_HPP

# include <utility>
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>
# include "ParserConfig.hpp"
# include "tools.hpp"

class AContext : public ParserConfig {

public:
	typedef std::vector<std::string>			tokensContainer;
	typedef tokensContainer::iterator			tokensIterator;
	typedef std::map<std::string, std::string>	directivesContainer;
	typedef directivesContainer::iterator		directivesIterator;

	AContext();
	AContext(const std::string &contextName);
	virtual ~AContext();

protected:
	void directiveReplaceInserter(directivesContainer &container, tokensIterator &it);
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
