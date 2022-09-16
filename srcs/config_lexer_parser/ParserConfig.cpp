/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:25 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 18:22:02 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserConfig.hpp"

ParserConfig::ParserConfig()
{}

ParserConfig::ParserConfig(const ParserConfig &src)
{ *this = src; }

/*
**	@brief ParserConfig constructor.
**	@param std::string corresponding to the context of the Context associated
**		   object.
**
**	For abstraction purpose in the Context class, string convertion to context
**	enum index is performed while contructing a ParserConfig object.
**
**	@warning This constructor MUST NOT be called with a string that does not ma-
**			 -tch any context in the keywords table. This check MUST be perform-
**			 -ed while instanciating a Context object as it should not be insta-
**			 -nciated if the context is not specified in the keywords table as a
**			 possible bloc. To prevent and detect any misuse, an exception is
**			 thrown but this case should not happen.
*/

ParserConfig::ParserConfig(const std::string &context, const std::string &parentName)
	: m_contextIndex(getContextIndex(context)),
	  m_contextName(context),
	  m_parentName(parentName)
{}

/*
** @brief ParserConfig default destructor. Does nothing.
*/

ParserConfig::~ParserConfig()
{}

ParserConfig &ParserConfig::operator=(const ParserConfig &rhs)
{
	if (this != &rhs)
	{
		this->m_contextIndex = rhs.m_contextIndex;
		this->m_contextName = rhs.m_contextName;
		this->m_parentName = rhs.m_parentName;
	}
	return *this;
}

const int &ParserConfig::getContextIndex() const
{ return this->m_contextIndex; }

const std::string &ParserConfig::getContextName() const
{ return this->m_contextName; }

const std::string &ParserConfig::getParentName() const
{ return this->m_parentName; }

/*
**	@brief Return the index of a keyword in the specified context.
**	@param keyword: The keyword whose index needs to be found.
**	@scope Private
*/

int	ParserConfig::getIndex(const std::string &keyword)
{
	int index = 0;
	while (keywords[m_contextIndex][index].keyword != keyword and not keywords[m_contextIndex][index].keyword.empty())
		index++;
	return index;
}

/*
**	@brief Return the index of a context as string in the contexts enum.
**	@param context: The context whose index needs to be found.
**	@scope Private
*/

int	ParserConfig::getContextIndex(const std::string &context)
{
	int index = 0;
	while (enumIndexes[index] != context and not enumIndexes[index].empty())
		index++;
	if (index == CONTEXTS_COUNT)
		throw std::out_of_range(PARSERCONFIG_MISUSE);
	return index;
}

/*
**	@brief Above funtions return the boolean corresponding to the function name
**		   for a keyword inside the specified context. Informations are taken
**		   from the keyword table file.
**	@param keyword: The keyword from which information is needed.
**	@scope Public
*/

bool ParserConfig::isPossible(const std::string &keyword)
{ return keywords[m_contextIndex][getIndex(keyword)].possible; }

bool ParserConfig::isMandatory(const std::string &keyword)
{ return keywords[m_contextIndex][getIndex(keyword)].mandatory; }

bool ParserConfig::isDirective(const std::string &keyword)
{ return keywords[m_contextIndex][getIndex(keyword)].isDirective; }

bool ParserConfig::isBloc(const std::string &keyword)
{ return keywords[m_contextIndex][getIndex(keyword)].isBloc; }

bool ParserConfig::isPossibleDirective(const std::string &keyword)
{ return isPossible(keyword) and isDirective(keyword); }

bool ParserConfig::isMandatoryDirective(const std::string &keyword)
{ return isMandatory(keyword) and isDirective(keyword); }

bool ParserConfig::isPossibleBloc(const std::string &keyword)
{ return isPossible(keyword) and isBloc(keyword); }

bool ParserConfig::isMandatoryBloc(const std::string &keyword)
{ return isMandatory(keyword) and isBloc(keyword); }

bool ParserConfig::contextNameRequiresURI(const std::string &parentContext, const std::string &context)
{
	m_contextIndex = getContextIndex(parentContext);
	bool ret = keywords[getContextIndex(parentContext)][getIndex(context)].hasUri;
	m_contextIndex = getContextIndex(context);
	return ret;
}

bool ParserConfig::contextNameRequiresURI(const std::string &context)
{ return keywords[m_contextIndex][getIndex(context)].hasUri; }
