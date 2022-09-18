/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:11:59 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/18 18:11:16 by cberganz         ###   ########.fr       */
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

Context::Context(const Context &src)
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
	getContextInformations();
	checkMandatoryDirectives();
	checkMandatoryContexts();
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
	: ContextBase(*tokensIt, parentContext.m_contextName)
{
	copyParentDirectives(parentContext.m_directives, m_directives);
	handleBlocOpening();
	getContextInformations();
	checkMandatoryDirectives();
	checkMandatoryContexts();
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

const std::map<std::string, Context> &Context::getContexts() const
{ return this->m_contexts; }

const ContextBase::directivesContainer &Context::getDirectives() const
{ return this->m_directives; }

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
	while (not (*tokensIt).empty() and *tokensIt != BLOC_END)
	{
		if (isPossibleDirective(*tokensIt))
			directiveReplaceInserter(m_directives);
		else if (isPossibleBloc(*tokensIt))
			m_contexts.insert(std::make_pair(getKeyIdentifier(m_contexts), Context(*this)));
		else
			throwException(UNAVAILABLE_DIRECTIVE, *tokensIt);
	}
	handleBlocEnding();
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
			if (indexMatchKeyword(index, (*it).second.m_contextName))
				break ;
			it++;
		}
		if (it == m_contexts.end())
			throwException(MANDATORY_CONTEXT_NOT_FOUND, getKeyword(index));
	}
}
