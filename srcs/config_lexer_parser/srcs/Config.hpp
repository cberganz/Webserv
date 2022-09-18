/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:39:47 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/18 20:39:44 by cberganz         ###   ########.fr       */
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
	typedef Parser::directivesContainer	directivesContainer;
	typedef Parser::directivesIterator	directivesIterator;
	typedef Parser::contextsContainer	contextsContainer;
	typedef Parser::contextsIterator	contextsIterator;

	Config();
	Config(const Config &src);
	Config(const std::string &fileName);
	~Config();

	Config &operator=(const Config &rhs);

	const Parser &getParser() const;

private:
	Parser m_parser;

};

// Bad ideas...
//operator[]: inside Config
//"global": return root context
//"server": return server contexts map in root
//ie. Config["server"][0] should return the first server of the global context as we are in a map
//
//operator[]: inside context


#endif
