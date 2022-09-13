/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:20 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 21:55:58 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlobalContext.hpp"

GlobalContext::GlobalContext()
	: AContext("Global")
{}

GlobalContext::GlobalContext(const tokensVector &tokens)
	: AContext("Global")
{
	getGlobalContext(tokens);
}

GlobalContext::~GlobalContext()
{}

const Server::serverMap &GlobalContext::getServers() const
{ return this->m_servers; }

const AContext::directiveMap &GlobalContext::getDirectives() const
{ return this->m_globalDirectives; }

void GlobalContext::getGlobalContext(const tokensVector &tokens)
{
	tokensConstIterator it = tokens.begin();
	while (it != tokens.end())
	{
		if (keywordExistsInContext(globalDirectives, *it))
		{
			containerReplaceInserter(m_globalDirectives, *it, std::make_pair(*it, *++it));
			*(++it) == ";" ? it++ : throw ParsingErrorException(*this, NO_SEMICOLON, *(it - 2));
		}
		else if (keywordExistsInContext(globalPossibleBlocs, *it))
			m_servers.insert(std::make_pair(m_servers.size(), Server(m_globalDirectives, tokens, it)));
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE, *it);
	}
}
