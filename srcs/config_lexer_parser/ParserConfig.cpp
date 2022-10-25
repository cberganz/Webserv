/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:25 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/25 17:00:16 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserConfig.hpp"

/*
**	@brief Default constructor for ParserConfig class.
**	@warning MUST NOT be used for instanciating ParserConfig directly.
*/

ParserConfig::ParserConfig()
{}

/*
**	@brief Copy constructor for ParserConfig class.
*/

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

ParserConfig::ParserConfig(const std::string &context,
						   const std::string &parentName)
	: m_contextIndex(getContextIndex(context)),
	  m_contextName(context),
	  m_parentName(parentName)
{}

/*
** @brief ParserConfig default destructor. Does nothing.
*/

ParserConfig::~ParserConfig()
{}

/*
**	@brief Copy assignement operator.
*/

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

/*
**	@brief ParserConfig accessors.
**	@scope Public
*/

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

int	ParserConfig::getKeywordIndex(const std::string &keyword) const
{
	int index = 0;
	while (keywords[m_contextIndex][index].keyword != keyword
		   and not keywords[m_contextIndex][index].keyword.empty())
		index++;
	return index;
}

/*
**	@brief Return the index of a context as string in the contexts enum.
**	@param context: The context whose index needs to be found.
**	@scope Private
*/

int	ParserConfig::getContextIndex(const std::string &context) const
{
	int index = 0;
	while (enumIndexes[index] != context and not enumIndexes[index].empty())
		index++;
	if (index == CONTEXTS_COUNT)
		throw std::out_of_range(PARSERCONFIG_MISUSE);
	return index;
}

/*
**	@brief Set of methods allowing access to parameters from the keywords table,
**		   using keywords taken as std::string.
**	@param keyword: The keyword from which information is needed as std::string.
**	@scope Protected
**
**	Above methods return a boolean representing the parameters for a keyword in-
**	-side the current context. Informations are stored in the keywords table. if
**	the keyword does not match any parameter, the current context default param-
**	-meter will be applied. Parameters and defaults can be changed from the key-
**	-words table.
*/

bool ParserConfig::isPossible(const std::string &keyword) const
{ return keywords[m_contextIndex][getKeywordIndex(keyword)].possible; }

bool ParserConfig::isMandatory(const std::string &keyword) const
{ return keywords[m_contextIndex][getKeywordIndex(keyword)].mandatory; }

bool ParserConfig::isDirective(const std::string &keyword) const
{ return keywords[m_contextIndex][getKeywordIndex(keyword)].isDirective; }

bool ParserConfig::isBloc(const std::string &keyword) const
{ return keywords[m_contextIndex][getKeywordIndex(keyword)].isBloc; }

bool ParserConfig::hasDefault(const std::string &keyword) const
{ return not keywords[m_contextIndex][getKeywordIndex(keyword)].dfault.empty(); }

bool ParserConfig::isPossibleDirective(const std::string &keyword) const
{ return isPossible(keyword) and isDirective(keyword); }

bool ParserConfig::isMandatoryDirective(const std::string &keyword) const
{ return isMandatory(keyword) and isDirective(keyword); }

bool ParserConfig::isPossibleBloc(const std::string &keyword) const
{ return isPossible(keyword) and isBloc(keyword); }

bool ParserConfig::isMandatoryBloc(const std::string &keyword) const
{ return isMandatory(keyword) and isBloc(keyword); }

bool ParserConfig::isMultiple(const std::string &keyword) const
{ return keywords[m_contextIndex][getKeywordIndex(keyword)].isMultiple; }

/*
**	@brief Set of methods allowing access to parameters from the keywords table,
**		   using indexes taken as int.
**	@param index: The index of an existing keyword.
**	@scope Protected
**
**	Above methods return a boolean representing the parameters for a keyword in-
**	-side the current context. Informations are stored in the keywords table and
**	parameters and defaults can be changed from the keywords table.
**
**	@warning MUST ALWAYS be used in a loop incrementing an index from zero until
**			 the return of indexIsDefault() is true. When this return value gets 
**			 true, you are matching the default settings.
*/

const std::string &ParserConfig::getKeyword(const int &index) const
{ return keywords[m_contextIndex][index].keyword; }

const std::string &ParserConfig::getDefault(const int &index) const
{ return keywords[m_contextIndex][index].dfault; }

bool ParserConfig::isPossible(const int &index) const
{ return keywords[m_contextIndex][index].possible; }

bool ParserConfig::isMandatory(const int &index) const
{ return keywords[m_contextIndex][index].mandatory; }

bool ParserConfig::isDirective(const int &index) const
{ return keywords[m_contextIndex][index].isDirective; }

bool ParserConfig::isBloc(const int &index) const
{ return keywords[m_contextIndex][index].isBloc; }

bool ParserConfig::hasDefault(const int &index) const
{ return not keywords[m_contextIndex][index].dfault.empty(); }

bool ParserConfig::isPossibleDirective(const int &index) const
{ return isPossible(index) and isDirective(index); }

bool ParserConfig::isMandatoryDirective(const int &index) const
{ return isMandatory(index) and isDirective(index); }

bool ParserConfig::isPossibleBloc(const int &index) const
{ return isPossible(index) and isBloc(index); }

bool ParserConfig::isMandatoryBloc(const int &index) const
{ return isMandatory(index) and isBloc(index); }

bool ParserConfig::isMultiple(const int &index) const
{ return keywords[m_contextIndex][index].isMultiple; }

bool ParserConfig::indexIsDefault(const int &index) const
{ return keywords[m_contextIndex][index].keyword.empty(); }

/*
**	@brief Determines whether an index match a specified keyword.
**	@param index: The index of an existing keyword.
**	@param keyword: The keyword to get match boolean.
**	@scope Protected
**
**	@warning MUST ALWAYS be used in a loop incrementing an index from zero until
**			 the return of indexIsDefault() is true.
*/

bool ParserConfig::indexMatchKeyword(const int &index,
									 const std::string &keyword) const
{ return keywords[m_contextIndex][index].keyword == keyword; }

/*
**	@brief The following functions checks whether a bloc requires an additional
**		   argument after the context name inside the configuration file.
**	The first version allows the parent context to check it before instanciating
**	a new Context. The second version allows the newly created object to know if
**	it has to handle it.
*/

bool ParserConfig::contextNameRequiresURI(const std::string &context) const
{ return keywords[m_contextIndex][getKeywordIndex(context)].hasUri; }

bool ParserConfig::contextNameRequiresURI(const std::string &parentContext,
										  const std::string &context)
{
	m_contextIndex = getContextIndex(parentContext);
	bool ret = keywords[getContextIndex(parentContext)][getKeywordIndex(context)].hasUri;
	m_contextIndex = getContextIndex(context);
	return ret;
}
