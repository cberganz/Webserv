/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:11:59 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 20:53:17 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"

Context::Context()
{}

Context::Context(const Context &src)
{ *this = src; }

Context::Context(tokensContainer &tokens)
	: ContextBase(tokens)
{
	getContextInformations();
	checkMandatoryDirectives();
	checkMandatoryContexts();
}

Context::Context(Context &parentContext)
	: ContextBase(*tokensIt, parentContext.m_contextName)
{
	copyParentDirectives(parentContext.m_directives);
	jumpBlocOpening();
	getContextInformations();
	checkMandatoryDirectives();
	checkMandatoryContexts();
}

Context::~Context()
{}

Context &Context::operator=(const Context &rhs)
{
	if (this != &rhs)
	{
		ContextBase::operator=(rhs);
		this->m_contexts = rhs.m_contexts;
		this->m_directives = rhs.m_directives;
	}
	return *this;
}

const std::map<std::string, Context> &Context::getContexts() const
{ return this->m_contexts; }

const ContextBase::directivesContainer &Context::getDirectives() const
{ return this->m_directives; }

void Context::getContextInformations()
{
	while (not (*tokensIt).empty() and *tokensIt != "}")
	{
		if (isPossibleDirective(*tokensIt))
			directiveReplaceInserter(m_directives);
		else if (isPossibleBloc(*tokensIt) and contextNameRequiresURI(*tokensIt))
			m_contexts.insert(std::make_pair(*(tokensIt + 1), Context(*this)));
		else if (isPossibleBloc(*tokensIt))
			m_contexts.insert(std::make_pair(ft::lexical_cast<std::string>(m_contexts.size()), Context(*this)));
		else
			throw ParsingErrorException(m_contextName, UNAVAILABLE_DIRECTIVE, *tokensIt);
	}
	jumpBlocEnding();
}

void Context::copyParentDirectives(directivesContainer &parentDirectives)
{
	for (directivesIterator it = parentDirectives.begin() ; it != parentDirectives.end() ; it++)
		if (isPossibleDirective((*it).first))
			directiveInserter(m_directives, it);
}

void Context::checkMandatoryDirectives()
{
	for (int i = 0 ; not keywords[m_contextIndex][i].keyword.empty() ; i++)
	{
		if (keywords[m_contextIndex][i].mandatory == false or keywords[m_contextIndex][i].isDirective == false)
			continue ;
		directivesIterator it = m_directives.begin();
		while (it != m_directives.end())
		{
			if (keywords[m_contextIndex][i].keyword == (*it).first)
				break ;
			it++;
		}
		if (it == m_directives.end())
		{
			if (keywords[m_contextIndex][i].dfault.empty())
				throw ParsingErrorException(m_contextName, MANDATORY_DIRECTIVE_NOT_FOUND, keywords[m_contextIndex][i].keyword);
			else
				m_directives.insert(std::make_pair(keywords[m_contextIndex][i].keyword, keywords[m_contextIndex][i].dfault));
		}
	}
}

void Context::checkMandatoryContexts()
{
	for (int i = 0 ; not keywords[m_contextIndex][i].keyword.empty() ; i++)
	{
		if (keywords[m_contextIndex][i].mandatory == false or keywords[m_contextIndex][i].isBloc == false)
			continue ;
		contextsIterator it = m_contexts.begin();
		while (it != m_contexts.end())
		{
			if (keywords[m_contextIndex][i].keyword == (*it).second.m_contextName)
				break ;
			it++;
		}
		if (it == m_contexts.end())
			throw ParsingErrorException(m_contextName, MANDATORY_CONTEXT_NOT_FOUND, keywords[m_contextIndex][i].keyword);
	}
}
