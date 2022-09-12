/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:20 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 18:27:05 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlobalContext.hpp"

GlobalContext::GlobalContext(const Lexer &lexer)
	: m_contextName("Global")
{
	getGlobalContext(lexer);
}

GlobalContext::~GlobalContext()
{}

const serverMap &GlobalContext::getServers() const
{ return this->m_servers; }

const directiveMap &GlobalContext::getDirectives() const
{ return this->m_globalDirectives; }

void GlobalContext::getGlobalContext(const Lexer &lexer)
{
	for (Lexer::iterator it = lexer.begin() ; it < lexer.end() ; it++)
	{
		if (keywordExistsInContext(globalDirectives, *it))
		{
			m_globalDirectives.erase(*it);
			m_globalDirectives.insert(make_pair(*it, *(++it)));
			if (*(++it) == ";")
				it++;
			else
				throw ParsingErrorException(*this, NO_SEMICOLON);
		}
		else if (keywordExistsInContext(globalPossibleBlocs, *it))
			m_servers.insert(make_pair(m_servers.size(), Server(m_globalDirectives, lexer, it)));
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE);
	}
}
