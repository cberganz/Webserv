/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:52 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 17:40:50 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"

class Parser {

public:
	typedef GlobalContext::serverMap		serverMap;
	typedef GlobalContext::serverIterator	serverIterator;
	typedef Server::locationMap				locationMap;
	typedef Server::LocationIterator		locationIterator;

	Parser(const std::string &fileName);
	~Parser();

private:
	Lexer		m_lexer;
	Global		m_globalContext;

};

#endif
