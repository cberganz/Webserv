#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include <map>
# include "AContext.hpp"

class Context : public AContext {

public:
	using typename AContext::tokensContainer;
	using typename AContext::tokensIterator;
	using typename AContext::directivesContainer;
	using typename AContext::directivesIterator;

	typedef std::map<std::string, Context>	contextsContainer;
	typedef contextsContainer::iterator		contextsIterator;

	Context();
	Context(const Context &src);
	Context(tokensContainer &tokens);
	Context(Context &parentContext);
	~Context();

	Context &operator=(const Context &rhs);

	const std::map<std::string, Context>	&getContexts()	 const;
	const AContext::directivesContainer		&getDirectives() const;

protected:
	contextsContainer		m_contexts;
	directivesContainer		m_directives;
	std::string				m_parentContext;
	static tokensIterator	tokensIt;

	void getContextInformations();
	void copyParentDirectives(directivesContainer &parentDirectives);

	void checkMandatoryDirectives();
	void checkMandatoryContexts();

};

#endif
