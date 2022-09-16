/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContext.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:02 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/15 22:24:28 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AContext.hpp"

AContext::AContext()
	: ParserConfig("")
{}

AContext::AContext(const std::string &contextName)
	: ParserConfig(contextName)
{}

AContext::~AContext()
{}

void AContext::directiveReplaceInserter(directivesContainer &container, tokensIterator &it)
{
	container.erase(*it);
	container.insert(std::make_pair(*it, *++it));
	if (*++it == ";")
		it++;
	else
		throw ParsingErrorException(m_contextName, NO_SEMICOLON, *(it - 2));
}

void AContext::directiveInserter(directivesContainer &container, directivesIterator &it)
{
	container.erase((*it).first);
	container.insert(std::make_pair((*it).first, (*it).second));
}

AContext::ParsingErrorException::ParsingErrorException(const std::string &contextName, const char *errorDetails, const std::string &token)
	: message("Error while parsing configuration file: Inside context: "
			  + contextName
			  + ": " + errorDetails
			  + ": \'" + token + "\'.")
{}

AContext::ParsingErrorException::~ParsingErrorException() throw()
{}

const char* AContext::ParsingErrorException::what() const throw()
{ return message.c_str(); }
