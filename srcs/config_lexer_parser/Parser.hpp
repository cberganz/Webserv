#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"

class Parser {

public:
	typedef GlobalContext::serverMap		serverMap;
	typedef GlobalContext::serverIterator	serverIterator;
	typedef Server::locationMap				locationMap;
	typedef Server::LocationIterator		locationIterator;

	Parser(const std::string &fileName);
	~Parser();

private:
	Lexer		m_lexer;
	Global		m_globalContext;

};

#endif
