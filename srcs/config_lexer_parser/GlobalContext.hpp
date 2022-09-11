#ifndef GLOBALCONTEXT_HPP
# define GLOBALCONTEXT_HPP

# include "AContext.hpp"

const std::string globalDirectives[] = {"root", ""};
const std::string globalPossibleBlocs[] = {"server", ""};

class GlobalContext : public AContext {

public:
	GlobalContext(const Lexer &lexer);
	~GlobalContext();

	const serverMap		&getServers() const;
	const directiveMap	&getDirectives() const;

private:
	serverMap		m_servers;
	directiveMap	m_globalDirectives;

	void getGlobalContext(const Lexer &lexer);

};

#endif


Global:
root
server

Server:
Listen
Location
root
server_name

Location:
Location
root
