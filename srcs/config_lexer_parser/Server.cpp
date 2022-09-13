/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 14:57:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 16:24:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const directiveMap &globalDirectives, const tokensVector &tokens, tokensConstIterator &it)
	: AContext("Server")
{
	for (directiveConstIterator it_dir = globalDirectives.begin() ; it_dir != globalDirectives.end() ; it_dir++)
		if (keywordExistsInContext(serverPossibleDirectives, (*it_dir).first))
			containerReplaceInserter(m_serverDirectives, (*it_dir).first, *it_dir);
	getServerContext(tokens, it);
	if (not checkMandatoryDirectives(serverMandatoryDirectives, m_serverDirectives))
		throw ParsingErrorException(*this, MANDATORY_DIRECTIVE_NOT_FOUND, "TEST"); //to change
}

Server::~Server()
{}

const Location::locationMap &Server::getLocations() const
{ return this->m_locations; }

const AContext::directiveMap &Server::getDirectives() const
{ return this->m_serverDirectives; }

void Server::getServerContext(const tokensVector &tokens, tokensConstIterator &it)
{
	*(++it) == "{" ? it++ : throw ParsingErrorException(*this, NO_BLOC_OPEN, *it);
	while (*it != "}")
	{
		if (keywordExistsInContext(serverPossibleDirectives, *it))
		{
			containerReplaceInserter(m_serverDirectives, *it, std::make_pair(*it, *++it));
			*(++it) == ";" ? it++ : throw ParsingErrorException(*this, NO_SEMICOLON, *(it - 2));
		}
		else if (keywordExistsInContext(serverPossibleBlocs, *it))
			m_locations.insert(std::make_pair(*(it + 1), Location(m_serverDirectives, tokens, it)));
		else if (it == tokens.end())
			throw ParsingErrorException(*this, UNEXPECTED_EOF, *--it);
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE, *it);
	}
	it++;
}
