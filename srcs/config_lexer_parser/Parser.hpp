/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 23:57:54 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <stdexcept>
# include "GlobalContext.hpp"
# include "Server.hpp"
# include "Location.hpp"

class Parser {

public:
	typedef std::vector<std::string>			tokensVector;
	typedef tokensVector::iterator				tokensIterator;
	typedef tokensVector::const_iterator		tokensConstIterator;
	typedef std::map<std::string, std::string>	directiveMap;
	typedef directiveMap::iterator				directiveIterator;
	typedef directiveMap::const_iterator		directiveConstIterator;
	typedef Server::serverMap					serverMap;
	typedef Server::serverIterator				serverIterator;
	typedef Server::serverConstIterator			serverConstIterator;
	typedef Location::locationMap				locationMap;
	typedef Location::locationIterator			locationIterator;
	typedef Location::locationConstIterator		locationConstIterator;

	Parser(const std::string &fileName);
	~Parser();

	const tokensVector	&getTokens();
	const GlobalContext &getGlobal();

private:
	tokensVector	m_tokens;
	GlobalContext	m_globalContext;

	void handleSpace(std::string::iterator &it);
	void handleCharToken(std::string::iterator &it);
	void handleComment(std::string::iterator &it);
	void handleVar(std::string::iterator &it);
	void handleKeyword(std::string::iterator &it);
	bool isKeyChar(const std::string::iterator &it) const;

	void getTokens(const std::string &filename);

	typedef void	(Parser::*func)(std::string::iterator &);
	typedef struct	s_funcPtr {
		std::string	pattern;
		func		ptr;
	} t_funcPtr;

};

#endif
