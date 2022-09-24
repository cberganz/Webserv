/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContextBase.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:02 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/23 12:37:49 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContextBase.hpp"

/*
**	@brief Instanciation of the tokensIt static member, an iterator pointing to
**		   the tokens container.
**
**	This static iterator has the same instance for all Context objects, making
**	it easier to iterate on the tokens on multiple contexts intanciations.
*/

ContextBase::tokensIterator ContextBase::tokensIt;

/*
**	@brief ContextBase default contructor.
*/

ContextBase::ContextBase()
{}

/*
**	@brief ContextBase copy contructor.
*/

ContextBase::ContextBase(const ContextBase &src)
{ *this = src; }

/*
**	@brief Constructor for the very first instanciation of a ContextBase
**		   object inside the Parser class. Used only for creating global
**		   context.
**	@param tokens: The tokens container parsed by the Parser class.
**
**	This consructor initialises the tokensIt static variable to the begin
**	of the tokens container so it MUST be called only once.
*/

ContextBase::ContextBase(const tokensContainer &tokens)
	: ParserConfig("global", "None")
{ tokensIt = tokens.begin(); }

/*
**	@brief Constructor for all other instanciations of a ContextBase.
**	@param parentName: Reference to string representing the name of the parent
**		   context.
**	@param contextName: Reference to string representing the name of the Context
**		   being instanciated.
*/

ContextBase::ContextBase(const std::string &contextName, const std::string &parentName)
	: ParserConfig(contextName, parentName)
{}

/*
**	@brief ContextBase destructor. Does nothing.
*/

ContextBase::~ContextBase()
{}

/*
**	@brief ContextBase copy assignement operator.
*/

ContextBase &ContextBase::operator=(const ContextBase &rhs)
{
	if (this != &rhs)
		ParserConfig::operator=(rhs);
	return *this;
}

/*
**	@brief Return current static token which is a private member.
*/

const std::string &ContextBase::getCurrentToken()
{ return *tokensIt; }

const std::string &ContextBase::getFollowingToken(const int &offset)
{ return *(tokensIt + offset); }

/*
**	@brief Get the keyword that should identify the context in the Contexts
**		   container.
**
**	Whenever a Context requires an URI specifier after the context name in the
**	configuration fie (ie. 'location / {}'), the Context will be identified by
**	it. If the context does not requires an URI, the keyword table MUST specify
**	a directive keyword to get this role so the following method can find it. If
**	there is no specified keyword, an exception is thrown.
*/

const std::string ContextBase::getKeyIdentifier()
{
	if (contextNameRequiresURI(*tokensIt))
		return *(tokensIt + 1);
	else
	{
		for (int offset = 0 ; *(tokensIt + offset) != "}" and *(tokensIt + offset) != "" ; offset++)
			if (*(tokensIt + offset) == "listen")
				return (*(tokensIt + offset + 1));
	}
	return "";
}

/*
**	@brief Allows secure jump of the bloc opening bracket.
**
**	Verify whether the syntax of the bloc opening is correct, even in the case
**	an URI specifier is required in this context. Throw two different exceptions
**	if the syntax is not correct : UNSPECIFIED_URI if an URI specifier is required
**	and not specified, NO_BLOC_OPEN if the bloc has no opening bracket.
*/

void ContextBase::handleBlocOpening()
{
	if (contextNameRequiresURI(m_parentName, m_contextName))
		*(tokensIt + 1) != BLOC_START ? static_cast<void>(tokensIt++) : throwException(UNSPECIFIED_URI, m_contextName);
	if (*++tokensIt == BLOC_START)
		tokensIt++;
	else
		throwException(NO_BLOC_OPEN, m_contextName);
}

/*
**	@brief Allows secure jump of the bloc ending bracket.
**
**	Verify whether the syntax of the bloc ending is correct. Throw an exception
**	if the bloc has no closing bracket.
*/

void ContextBase::handleBlocEnding()
{
	if (m_contextIndex != GLOBAL and *tokensIt == BLOC_END)
		tokensIt++;
	else if (m_contextIndex != GLOBAL)
		throwException(UNEXPECTED_EOF, m_contextName);
}

/*
**	@brief Tool to perform replacement of directives in the case it already exists.
**	@param container: Reference to the m_directives container of the associated
**		   Context object as it is not accessible in this scope.
**
**	Use erase and insert methods from the directives container to perfom replacement.
**	Then checks whether the syntax of the line is good, throwing an exception if the
**	next token is not a semicolon.
*/

void ContextBase::directiveInserter(directivesContainer &container)
{
	if (container.find(*tokensIt) == container.end())
		container.insert(std::make_pair(*tokensIt, *++tokensIt));
	else
		throwException(DUPLICATE_DIRECTIVE, *tokensIt);
	if (*++tokensIt == DIRECTIVE_END)
		tokensIt++;
	else
		throwException(NO_SEMICOLON, *(tokensIt - 2));
}

/*
**	@brief Tool to perform copy of the parent Context object directives.
**	@param container: Reference to the m_directives container of the associated
**		   Context object as it is not accessible in this scope.
**
**	Use insert methods from the directives container to perfom copy.
*/

void ContextBase::copyParentDirectives(directivesContainer &parentContainer,
									   directivesContainer &container)
{
	for (directivesIterator it = parentContainer.begin() ; it != parentContainer.end() ; it++)
		if (isPossibleDirective((*it).first) and container.count((*it).first) == 0)
				container.insert(std::make_pair((*it).first, (*it).second));
}

/*
**	@brief Performs insertion of default value for mandatory directives that
**		   was not found in the configuration file. Throw an exception if no
**		   default is set.
**	@param container: The directives container in wich insertion should be done.
**	@param index: The index of the directive in the keywords table.
*/

void ContextBase::insertDefaultIfExistingOrThrowException(directivesContainer &container,
														  const int &index)
{
	if (hasDefault(index))
		container.insert(std::make_pair(getKeyword(index), getDefault(index)));
	else
		throwException(MANDATORY_DIRECTIVE_NOT_FOUND, getKeyword(index));
}

/*
**	@brief Implementation of the ParsingErrorException member class.
**	@param contextName: The name of the context where the error occured.
**	@param errorDetails: The details of the occuring error. Can refer to
**		   an error defined in the parsingErrors.hpp header.
**	@param token: The token on which the error occured.
*/

ContextBase::ParsingErrorException::ParsingErrorException(const std::string &contextName,
														  const char *errorDetails,
														  const std::string &word)
	: message("Error while parsing configuration file: Inside context: "
			  + contextName
			  + ": " + errorDetails
			  + ": \'" + word + "\'.")
{}

ContextBase::ParsingErrorException::~ParsingErrorException() throw()
{}

const char* ContextBase::ParsingErrorException::what() const throw()
{ return message.c_str(); }

void ContextBase::throwException(const char *errorDetails, const std::string &word) const
{ throw ParsingErrorException(m_contextName, errorDetails, word); }
