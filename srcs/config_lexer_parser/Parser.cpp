#include "Parser.hpp"

Parser::Parser(const std::string &fileName)
	: m_lexer(Lexer(fileName)),
	  m_globalContext(m_lexer)
{}

Parser::~Parser()
{}
