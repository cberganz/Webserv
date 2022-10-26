/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:11:59 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/26 13:54:25 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"

/*
**	@brief Default constructor.
*/

Context::Context()
{}

/*
**	@brief Copy constructor.
*/

Context::Context(const Context &src) :
	ContextBase()
{ *this = src; }

/*
**	@brief Constructor for the very first instanciation of a Context object
**		   inside the Parser class. Used only for creating global context.
**	@param tokens: The tokens container parsed by the Parser class.
**
**	This constructor does not perform copy of the parent context directives
**	as there is no parent for the global context.
*/

Context::Context(const tokensContainer &tokens)
	: ContextBase(tokens)
{
	handleNewline();
	getContextInformations();
}

/*
**	@brief Constructor for all other instanciations of a context, called in
**		   the parent context object.
**	@param parentContext: Reference to the Context object that has created
**		   the current object.
**
**	This constructor perform copy of parent context directives. 
*/

Context::Context(Context &parentContext)
	: ContextBase(parentContext.getCurrentToken(), parentContext.m_contextName)
{
	handleBlocOpening();
	getContextInformations();
	copyParentDirectives(parentContext.m_directives, m_directives);
}

/*
**	@brief Context destructor. Does nothing.
*/

Context::~Context()
{}

/*
**	@brief Copy assignement operator.
*/

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

/*
**	@brief Context accessors.
*/

std::map<std::string, Context> &Context::getContexts()
{ return this->m_contexts; }

ContextBase::directivesContainer &Context::getDirectives()
{ return this->m_directives; }

const std::map<std::string, Context> &Context::getContexts() const
{ return this->m_contexts; }

const ContextBase::directivesContainer &Context::getDirectives() const
{ return this->m_directives; }

const Context &Context::getContext(const std::string &contextName) const
{ return m_contexts.at(contextName); }

const std::vector<std::string> &Context::getDirective(const std::string &directiveName) const
{ return m_directives.at(directiveName); }

bool Context::directiveExist(const std::string &directive) const
{ return m_directives.count(directive); }

bool Context::contextExist(const std::string &contextName) const
{ 
	try {
		this->getContext(contextName);
	}
	catch (const std::out_of_range &e) {
		return (false);
	}
	return (true);
}

/*
**	@brief Parse the context informations inside the tokens container.
**
**	Perform insertion of the directives found inside the current bloc to the
**	directives container of the current instance. If a directive has already
**	been taken from the parent context, replace it. If a new bloc is found 
**	inside the current bloc, creates a new context object to parse it and 
**	insert this object in the contexts container of the current context. if
**	a keyword found does not exists, throw an exception.
*/

void Context::getContextInformations()
{
	while (not getCurrentToken().empty() and getCurrentToken() != BLOC_END)
	{
		if (isPossibleDirective(getCurrentToken()))
			directiveInserter(m_directives);
		else if (isPossibleBloc(getCurrentToken()))
			blocInserter();
		else
			throwException(UNAVAILABLE_DIRECTIVE, getCurrentToken());
	}
	handleBlocEnding();
}

/*
**	@brief Context container insertion tool. Also throw exception if the bloc
**		   was previously encontered in the same context whith the same key
**		   identifier.
*/

void Context::blocInserter()
{
	if (m_contexts.find(getKeyIdentifier()) != m_contexts.end() and m_contextName != "global")
		throwException(DUPLICATE_BLOC, getCurrentToken());
	m_contexts.insert(std::make_pair(getKeyIdentifier(), Context(*this)));
}

/*
**	@brief Checker whether all the mandatory directives of the context were found.
**
**	If a mandatory directive is not found, check if a default value is set in the
**	keywords table. If a default exists, insert it in the directives container,
**	otherwise throw an exception.
*/

void Context::checkMandatoryDirectives()
{
	for (int index = 0 ; not indexIsDefault(index) ; index++)
	{
		if (not isMandatoryDirective(index))
			continue ;
		directivesConstIterator it = m_directives.begin();
		while (it != m_directives.end())
		{
			if (indexMatchKeyword(index, (*it).first))
				break ;
			it++;
		}
		if (it == m_directives.end())
			insertDefaultIfExistingOrThrowException(m_directives, index);
	}
}

/*
**	@brief Checker whether all the mandatory blocs of the context were found.
**		   Throw an exception if a bloc is missing.
*/

void Context::checkMandatoryContexts() const
{
	for (int index = 0 ; not indexIsDefault(index) ; index++)
	{
		if (not isMandatoryBloc(index))
			continue ;
		contextsConstIterator it = m_contexts.begin();
		while (it != m_contexts.end())
		{
			if (indexMatchKeyword(index, (*it).second.getContextName()))
				break ;
			it++;
		}
		if (it == m_contexts.end())
			throwException(MANDATORY_CONTEXT_NOT_FOUND, getKeyword(index));
	}
}
