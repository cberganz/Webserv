/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/19 21:52:41 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include <string>
# include <vector>
# include <map>
# include "ContextBase.hpp"

/*
**	@brief Class representing any type of context to parse it.
**	@category class
**
**	This composite pattern template class can be instanciated to represent any
**	type of context that can be found in the configuration file, depending on
**	keywords table. At construction time, it will parse the tokens inside the
**	bloc to store directives and generate childs contexts. When instanciated
**	for the first time from the global context, it results in a tree of contexts
**	representing the configuration file informations with the root of the three
**	being the global context.
*/

class Context : public ContextBase {

public:
	using typename ContextBase::tokensContainer;
	using typename ContextBase::tokensIterator;
	using typename ContextBase::directivesContainer;
	using typename ContextBase::directivesIterator;
	using typename ContextBase::directivesConstIterator;

	typedef std::map<std::string, Context>	  contextsContainer;
	typedef contextsContainer::iterator		  contextsIterator;
	typedef contextsContainer::const_iterator contextsConstIterator;

	Context();
	Context(const Context &src);
	Context(const tokensContainer &tokens);
	Context(Context &parentContext);
	~Context();

	Context &operator=(const Context &rhs);

	const std::map<std::string, Context>	&getContexts()	 const;
	const ContextBase::directivesContainer	&getDirectives() const;

protected:
	contextsContainer		m_contexts;
	directivesContainer		m_directives;

	void getContextInformations();
	void blocInserter();

	void checkMandatoryDirectives();
	void checkMandatoryContexts() const;

}; // class Context

#endif // CONTEXT_HPP
