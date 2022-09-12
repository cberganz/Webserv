/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:39 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 17:42:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location(const directiveMap &serverDirectives, const lexerVector &tokens, lexerIterator &it)
	: m_contextName("Location")
{
	for (directiveIterator it = serverDirectives.begin() ; it < serverDirectives.end() ; it++)
	{
		if (keywordExistsInContext(locationPossibleDirectives, (*it).first))
		{
			m_locationDirectives.erase(*it);
			m_locationDirectives.insert(*it); // is it ok to insert *it or should I insert make_pair?
		}
	}
	getLocationContext(tokens, it);
	if (not checkMandatoryDirectives(locationMandatoryDirectives, m_locationDirectives))
		throw ParsingErrorException(*this, MANDATORY_DIRECTIVE_NOT_FOUND);
}

Location::~Location()
{

}

const directiveMap &Location::getDirectives() const
{ return this->m_locationDirectives; }

void Location::getLocationContext(const lexerVector &tokens, lexerIterator &it)
{
	if (*(++it) == "{")
		it++;
	else
		throw ParsingErrorException(*this, NO_BLOC_OPEN);
	while (*it != "}")
	{
		if (keywordExistsInContext(locationPossibleDirectives, *it))
		{
			m_locationDirectives.erase(*it);
			m_locationDirectives.insert(make_pair(*it, *(++it)));
			if (*(++it) == ";")
				it++;
			else
				throw ParsingErrorException(*this, NO_SEMICOLON);
		}
		else if (it == tokens.end())
			throw ParsingErrorException(*this, UNEXPECTED_EOF);
		else
			throw ParsingErrorException(*this, UNAVAILABLE_DIRECTIVE);
	}
	it++;
}
