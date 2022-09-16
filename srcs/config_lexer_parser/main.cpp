#include <iostream>
#include <iomanip>
#include <string>
#include "Parser.hpp"

void printTab(int tabCount)
{
	for (int i = 0 ; i < tabCount ; i++)
		std::cout << "\t";
}

void printDirectives(const Parser::directivesContainer &directives, int tabCount)
{
	for (Parser::directivesContainer::const_iterator it = directives.begin() ;
		 it != directives.end() ; it++)
	{
		printTab(tabCount);
		std::cout << (*it).first << " -> " << (*it).second << std::endl;
	}
	std::cout << std::endl;
}

void RContextsContainer(const Parser::contextsContainer &contexts, int tabCount)
{
	for (Parser::contextsContainer::const_iterator it = contexts.begin() ;
		 it != contexts.end() ; it++)
	{
		printTab(tabCount);
		std::cout << "[" << (*it).second.getContextName() << "]" << std::endl;
		printDirectives((*it).second.getDirectives(), tabCount);
		if (not (*it).second.getContexts().empty() and )
			RContextsContainer((*it).second.getContexts(), ++tabCount);
	}
}

int main()
{
	try {
		Parser parser("test.txt");
		Parser::contextsContainer cont;
		cont.insert(std::make_pair("global", parser.getGlobal()));
		RContextsContainer(cont, 0);
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
