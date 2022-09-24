/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/23 03:34:05 by charles          ###   ########.fr       */
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
{
	checkMandatories(m_root);
	m_root.checkMandatoryDirectives();
	m_root.checkMandatoryContexts();
}

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

void Parser::checkMandatories(Context &context)
{
	for (contextsIterator it = context.getContexts().begin() ; it != context.getContexts().end() ; it++)
	{
		m_root.copyParentDirectives(context.getDirectives(), (*it).second.getDirectives());
		checkMandatories((*it).second);
		(*it).second.checkMandatoryDirectives();
		(*it).second.checkMandatoryContexts();
	}
}
