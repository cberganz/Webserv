/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:48 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 11:10:48 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::string &fileName)
	: m_lexer(Lexer(fileName)),
	  m_globalContext(m_lexer)
{}

Parser::~Parser()
{}
