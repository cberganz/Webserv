/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:39:47 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/25 16:50:55 by cberganz         ###   ########.fr       */
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

	const Context &getServer(const std::string& ip, const std::string& port) const
	{
		for (contextsContainer::const_iterator it = m_parser.getRoot().getContexts().begin() ;
			 it != m_parser.getRoot().getContexts().end() ; it++)
			if (it->second.getDirective("ip")[0] == ip and it->second.getDirective("port")[0] == port)
				return it->second;
		for (contextsContainer::const_iterator it = m_parser.getRoot().getContexts().begin() ;
			 it != m_parser.getRoot().getContexts().end() ; it++)
			if (it->second.getDirective("ip")[0] == "0.0.0.0" and it->second.getDirective("port")[0] == port)
				return it->second;
		return m_parser.getRoot().getContexts().begin()->second;
	}

	const Context &getServer(const std::string& ip, const std::string& port, const std::string& server_name) const
	{
		for (contextsContainer::const_iterator it = m_parser.getRoot().getContexts().begin() ;
			 it != m_parser.getRoot().getContexts().end() ; it++)
			if (it->second.getDirective("ip")[0] == ip and it->second.getDirective("port")[0] == port and it->second.getDirective("server_name")[0] == server_name)
				return it->second;
		for (contextsContainer::const_iterator it = m_parser.getRoot().getContexts().begin() ;
			 it != m_parser.getRoot().getContexts().end() ; it++)
			if (it->second.getDirective("ip")[0] == ip and it->second.getDirective("port")[0] == port)
				return it->second;
		for (contextsContainer::const_iterator it = m_parser.getRoot().getContexts().begin() ;
			 it != m_parser.getRoot().getContexts().end() ; it++)
			if (it->second.getDirective("ip")[0] == "0.0.0.0" and it->second.getDirective("port")[0] == port)
				return it->second;
		return m_parser.getRoot().getContexts().begin()->second;
	}

private:
	Parser m_parser;

}; // class Config

#endif // CONFIG_HPP
