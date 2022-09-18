/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/18 19:56:05 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
{}

Parser::Parser(const Parser &src)
{ *this = src; }

Parser::Parser(const std::string &fileName)
	: Lexer(fileName),
	  m_root(getTokens())
{}

Parser::~Parser()
{}

Parser &Parser::operator=(const Parser &rhs)
{
	if (this != &rhs)
	{
		Lexer::operator=(rhs);
		m_root = rhs.m_root;
	}
	return *this;
}

const Context &Parser::getRoot() const
{ return this->m_root; }
