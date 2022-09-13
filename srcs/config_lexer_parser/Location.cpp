/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:39 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 16:24:27 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(const directiveMap &serverDirectives, const tokensVector &tokens, tokensConstIterator &it)
	: AContext("Location")
{
	for (directiveConstIterator it_dir = serverDirectives.begin() ; it_dir != serverDirectives.end() ; it_dir++)
		if (keywordExistsInContext(locationPossibleDirectives, (*it_dir).first))
			containerReplaceInserter(m_locationDirectives, (*it_dir).first, *it_dir);
	getLocationContext(tokens, it);
	if (not checkMandatoryDirectives(locationMandatoryDirectives, m_locationDirectives))
		throw ParsingErrorException(*this, MANDATORY_DIRECTIVE_NOT_FOUND, "TEST"); // to change
}

Location::~Location()
{}

const AContext::directiveMap &Location::getDirectives() const
{ return this->m_locationDirectives; }

void Location::getLocationContext(const tokensVector &tokens, tokensConstIterator &it)
{
	*(++it) != "{" ? it++ : throw ParsingErrorException(*this, NO_BLOC_OPEN, *it);
	*it == "{" ? it++ : throw ParsingErrorException(*this, NO_SPECIFIED_LOCATION, *(it - 2));
	while (*it != "}")
	{
		if (keywordExistsInContext(locationPossibleDirectives, *it))
		{
			containerReplaceInserter(m_locationDirectives, *it, std::make_pair(*it, *++it));
			*(++it) == ";" ? it++ : throw ParsingErrorException(*this, NO_SEMICOLON, *(it - 2));
		}
		else if (it == tokens.end())
			throw ParsingErrorException(*this, UNEXPECTED_EOF, *--it);
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE, *it);
	}
	it++;
}
