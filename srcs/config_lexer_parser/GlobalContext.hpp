#ifndef GLOBALCONTEXT_HPP
# define GLOBALCONTEXT_HPP

# include <utility>

const std::string serverDirectives[] = {"root", ""};

class GlobalContext {

public:
	typedef std::map<std::string, std::string>	serverDirectiveMap;
	typedef std::map<int, Server>				serverMap;
	typedef serverMap::iterator					serverIterator;

	GlobalContext(const Lexer &lexer);
	~GlobalContext();

private:
	serverMap			m_servers;
	serverDirectiveMap	m_directives;

	void getGlobalContext(const Lexer &lexer);
	bool directiveExists(const std::string &directive);

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
