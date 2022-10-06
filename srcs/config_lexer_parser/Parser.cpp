/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/06 02:16:24 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
	: Lexer(),
	  m_root()
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
	setServersIpsAndPorts(m_root);
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

void Parser::setServersIpsAndPorts(Context &context)
{
	for (contextsIterator it = context.getContexts().begin() ; it != context.getContexts().end() ; it++)
	{
		if ((*it).second.getContextName() == "server")
		{
			std::string s = *(*it).second.getDirective("listen").begin();
			std::vector<std::string> tmp;
			tmp.push_back(s.substr(0, s.find(":")));
			(*it).second.getDirectives().insert(std::make_pair("ip", tmp));
			tmp.clear();
			tmp.push_back(s.substr(s.find(":") + 1, s.size()));
			(*it).second.getDirectives().insert(std::make_pair("port", tmp));
		}
	}
}
