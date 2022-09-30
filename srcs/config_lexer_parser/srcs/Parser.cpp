/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 02:54:33 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
	: Context(),
	  m_lexer()
{}

Parser::Parser(const Parser &src)
{ *this = src; }

Parser::Parser(const std::string &fileName)
	: m_lexer(fileName)
{
	Context::operator=(Context(m_lexer.getTokens()));
	checkMandatories(*this);
	checkMandatoryDirectives();
	checkMandatoryContexts();
	setServersIpsAndPorts(*this);
}

Parser::~Parser()
{}

Parser &Parser::operator=(const Parser &rhs)
{
	if (this != &rhs)
	{
		Context::operator=(rhs);
		m_lexer = rhs.m_lexer;
	}
	return *this;
}

void Parser::checkMandatories(Context &context)
{
	for (contextsIterator it = context.getContexts().begin() ; it != context.getContexts().end() ; it++)
	{
		copyParentDirectives(context.getDirectives(), (*it).second.getDirectives());
		checkMandatories((*it).second);
		(*it).second.checkMandatoryDirectives();
		(*it).second.checkMandatoryContexts();
	}
}

void Parser::setServersIpsAndPorts(Context &context)
{
	for (contextsIterator it = context.getContexts().begin() ; it != context.getContexts().end() ; it++)
	{
		if ((*it).second.getContextName() == "server")
		{
			std::string s = (*it).second.getDirective("listen");
			(*it).second.getDirectives().insert(std::make_pair("ip", s.substr(0, s.find(":"))));
			(*it).second.getDirectives().insert(std::make_pair("port", s.substr(s.find(":") + 1, s.size())));
		}
	}
}
