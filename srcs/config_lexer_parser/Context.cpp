#include "Context.hpp"

Context::tokensIterator Context::tokensIt;

Context::Context()
{}

Context::Context(const Context &src)
{ *this = src; }

Context::Context(tokensContainer &tokens)
	: AContext("global"), m_parentContext("None")
{
	tokensIt = tokens.begin();
	getContextInformations();
	checkMandatoryDirectives();
	checkMandatoryContexts();
}

Context::Context(Context &parentContext)
	: AContext(*tokensIt), m_parentContext(parentContext.m_contextName)
{
	copyParentDirectives(parentContext.m_directives);
	if (*(tokensIt + 1) != "{" and contextNameRequiresURI(m_parentContext, m_contextName))
		tokensIt++;
	//else if (*(tokensIt + 1) == "{" and contextNameRequiresURI(m_parentContext, m_contextName))
		//ERROR URI NOT SPECIFIED
	if (*++tokensIt == "{")
		tokensIt++;
	else
		throw ParsingErrorException(m_contextName, NO_BLOC_OPEN, m_contextName);
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
		AContext::operator=(rhs);
		this->m_contexts = rhs.m_contexts;
		this->m_directives = rhs.m_directives;
		this->m_parentContext = rhs.m_parentContext;
	}
	return *this;
}

const std::map<std::string, Context> &Context::getContexts() const
{ return this->m_contexts; }

const AContext::directivesContainer &Context::getDirectives() const
{ return this->m_directives; }

void Context::getContextInformations()
{
	while (not (*tokensIt).empty() and *tokensIt != "}")
	{
		if (isPossibleDirective(*tokensIt))
			directiveReplaceInserter(m_directives, tokensIt);
		else if (isPossibleBlock(*tokensIt) and contextNameRequiresURI(*tokensIt))
			m_contexts.insert(std::make_pair(*(tokensIt + 1), Context(*this)));
		else if (isPossibleBlock(*tokensIt))
			m_contexts.insert(std::make_pair(ft::lexical_cast<std::string>(m_contexts.size()), Context(*this)));
		else
			throw ParsingErrorException(m_contextName, UNAVAILABLE_DIRECTIVE, *tokensIt);
	}
	if (m_contextIndex != GLOBAL and *tokensIt == "}")
		tokensIt++;
	else if (m_contextIndex != GLOBAL)
		throw ParsingErrorException(m_contextName, UNEXPECTED_EOF, m_contextName);
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
			throw ParsingErrorException(m_contextName, MANDATORY_DIRECTIVE_NOT_FOUND, keywords[m_contextIndex][i].keyword);
	}
}

void Context::checkMandatoryContexts()
{
	for (int i = 0 ; not keywords[m_contextIndex][i].keyword.empty() ; i++)
	{
		if (keywords[m_contextIndex][i].mandatory == false or keywords[m_contextIndex][i].isBlock == false)
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
