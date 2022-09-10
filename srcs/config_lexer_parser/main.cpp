#include <iostream>
#include <iomanip>
#include <string>
#include "Lexer.hpp"

int main()
{
	Lexer lex("test.txt");

	std::cout << "[";
	for (Lexer::iterator it = lex.begin() ; it < lex.end() ; it++)
		std::cout << *it << " - ";
	std::cout << "]" << std::endl;
	return 0;
}
