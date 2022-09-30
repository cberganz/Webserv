/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:39:47 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 05:09:43 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Parser.hpp"
# include "Context.hpp"

/*
**	@brief The purpose of this class is to be the external access point to use
**		   and access the datas parsed from the configuration file.
**
**	This class initialize the parsing and implements various access methods to
**	easily access datas from it.
**
**	@TODO IN CONSTRUCTION... Please come back later.
*/

class Config {

public:
	typedef Parser::directivesContainer		directivesContainer;
	typedef Parser::directivesIterator		directivesIterator;
	typedef Parser::directivesConstIterator	directivesConstIterator;
	typedef Parser::contextsContainer		contextsContainer;
	typedef Parser::contextsIterator		contextsIterator;
	typedef Parser::contextsConstIterator	contextsConstIterator;

	Config();
	Config(const Config &src);
	Config(const std::string &fileName);
	~Config();

	Config &operator=(const Config &rhs);

	const Parser &getParser() const;
	const contextsContainer &getGlobalContextsContainer() const;

	const Context &operator[](const std::string &contextName) const
	{
		if (contextName == "global")
			return m_parser.getRoot();
		else
			return m_parser.getRoot().getContexts().at(contextName);
	}

private:
	Parser m_parser;

}; // class Config

#endif // CONFIG_HPP
