/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:57:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 17:42:00 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const directiveMap &globalDirectives, const lexerVector &tokens, lexerIterator &it)
	: m_contextName("Server")
{
	for (directiveIterator it = globalDirectives.begin() ; it < globalDirectives.end() ; it++)
	{
		if (keywordExistsInContext(serverPossibleDirectives, (*it).first))
		{
			m_serverDirectives.erase(*it);
			m_serverDirectives.insert(*it); // is it ok to insert *it or should I insert make_pair?
		}
	}
	getServerContext(tokens, it);
	if (not checkMandatoryDirectives(serverMandatoryDirectives, m_serverDirectives))
		throw ParsingErrorException(*this, MANDATORY_DIRECTIVE_NOT_FOUND);
}

Server::~Server()
{}

const locationMap &Server::getlocations() const
{ return this->m_locations; }

const directiveMap &Server::getDirectives() const
{ return this->m_serverDirectives; }

void Server::getServerContext(const lexerVector &tokens, lexerIterator &it)
{
	if (*(++it) == "{")
		it++;
	else
		throw ParsingErrorException(*this, NO_BLOC_OPEN);
	while (*it != "}")
	{
		if (keywordExistsInContext(serverPossibleDirectives, *it))
		{
			m_serverDirectives.erase(*it);
			m_serverDirectives.insert(make_pair(*it, *(++it)));
			if (*(++it) == ";")
				it++;
			else
				throw ParsingErrorException(*this, NO_SEMICOLON);
		}
		else if (keywordExistsInContext(serverPossibleBlocs, *it))
			m_locations.insert(make_pair(m_locations.size(), Location(m_serverDirectives, it)));
		else if (it == tokens.end())
			throw ParsingErrorException(*this, UNEXPECTED_EOF);
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE);
	}
	it++;
}
