/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 17:28:26 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include <map>
# include "ContextBase.hpp"

class Context : public ContextBase {

public:
	using typename ContextBase::tokensContainer;
	using typename ContextBase::tokensIterator;
	using typename ContextBase::directivesContainer;
	using typename ContextBase::directivesIterator;

	typedef std::map<std::string, Context>	contextsContainer;
	typedef contextsContainer::iterator			contextsIterator;

	Context();
	Context(const Context &src);
	Context(tokensContainer &tokens);
	Context(Context &parentContext);
	~Context();

	Context &operator=(const Context &rhs);

	const std::map<std::string, Context>	&getContexts()	 const;
	const ContextBase::directivesContainer	&getDirectives() const;

protected:
	contextsContainer		m_contexts;
	directivesContainer		m_directives;

	void getContextInformations();
	void copyParentDirectives(directivesContainer &parentDirectives);

	void checkMandatoryDirectives();
	void checkMandatoryContexts();

};

#endif
