/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextBase.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:02 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 17:19:31 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContextBase.hpp"

ContextBase::tokensIterator ContextBase::tokensIt;

ContextBase::ContextBase()
{}

ContextBase::ContextBase(const ContextBase &src)
{ *this = src; }

ContextBase::ContextBase(tokensContainer &tokens)
	: ParserConfig("global", "None")
{ tokensIt = tokens.begin(); }

ContextBase::ContextBase(const std::string &contextName, const std::string &parentName)
	: ParserConfig(contextName, parentName)
{}

ContextBase::~ContextBase()
{}

ContextBase &ContextBase::operator=(const ContextBase &rhs)
{
	if (this != &rhs)
		ParserConfig::operator=(rhs);
	return *this;
}

void ContextBase::jumpBlocOpening()
{
	if (contextNameRequiresURI(m_parentName, m_contextName))
		*(tokensIt + 1) != "{" ? tokensIt++ : throw ParsingErrorException(m_contextName, UNSPECIFIED_URI, m_contextName);
	if (*++tokensIt == "{")
		tokensIt++;
	else
		throw ParsingErrorException(m_contextName, NO_BLOC_OPEN, m_contextName);
}

void ContextBase::jumpBlocEnding()
{
	if (m_contextIndex != GLOBAL and *tokensIt == "}")
		tokensIt++;
	else if (m_contextIndex != GLOBAL)
		throw ParsingErrorException(m_contextName, UNEXPECTED_EOF, m_contextName);
}

void ContextBase::directiveReplaceInserter(directivesContainer &container)
{
	container.erase(*tokensIt);
	container.insert(std::make_pair(*tokensIt, *++tokensIt));
	if (*++tokensIt == ";")
		tokensIt++;
	else
		throw ParsingErrorException(m_contextName, NO_SEMICOLON, *(tokensIt - 2));
}

void ContextBase::directiveInserter(directivesContainer &container, directivesIterator &it)
{
	container.erase((*it).first);
	container.insert(std::make_pair((*it).first, (*it).second));
}

ContextBase::ParsingErrorException::ParsingErrorException(const std::string &contextName, const char *errorDetails, const std::string &token)
	: message("Error while parsing configuration file: Inside context: "
			  + contextName
			  + ": " + errorDetails
			  + ": \'" + token + "\'.")
{}

ContextBase::ParsingErrorException::~ParsingErrorException() throw()
{}

const char* ContextBase::ParsingErrorException::what() const throw()
{ return message.c_str(); }
