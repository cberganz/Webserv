#include "GlobalContext.hpp"

bool GlobalContext::directiveExists(const std::string &directive)
{
	for (int i = 0 ; not serverDirectives[i].empty() ; i++)
	{
		if (serverDirectives[i] == directive)
			return true;
	}
	return false;
}

void GlobalContext::getGlobalContext(const Lexer &lexer)
{
	for (lexer::iterator it = lexer.begin() ; it < lexer.end() ; it++)
	{
		if (directiveExists(*it))
		{
			if (NOTAVALIDFORMAT(*it, *(it + 1)))
				//EXIT ERROR
			m_directives.insert(make_pair(*it, *(++it)));
			it++;
		}
		else if (not directiveExists(*it))
			//EXIT ERROR
		else if (*it == server)
			m_servers.insert(make_pair(m_servers.size(), Server(*this, it)));
	}
}
