#include <iostream>
#include <iomanip>
#include <string>
#include "Parser.hpp"

int main()
{
	try {
		Parser parser("test.txt");

		//const Parser::directiveMap globalDirectives = parser.getGlobal().getDirectives();
		//for (Parser::directiveConstIterator it = globalDirectives.begin() ;
		//	 it != globalDirectives.end() ; it++)
		//	std::cout << (*it).first << " -> " << (*it).second << std::endl;
		//std::cout << std::endl;

		//const Parser::serverMap servers = parser.getGlobal().getServers();
		//for (Parser::serverConstIterator it_s = servers.begin(); it_s != servers.end() ; it_s++)
		//{
		//	std::cout << "\tSERVER_BLOC[" << (*it_s).first << "]" << std::endl;	
		//	const Parser::directiveMap serverDirectives = (*it_s).second.getDirectives();
		//	for (Parser::directiveConstIterator it_s_i = serverDirectives.begin() ;
		//		 it_s_i != serverDirectives.end() ; it_s_i++)
		//		std::cout << "\t" << (*it_s_i).first << " -> " << (*it_s_i).second << std::endl;
		//	std::cout << std::endl;

		//	const Parser::locationMap locations = (*it_s).second.getLocations();
		//	for (Parser::locationConstIterator it_l = locations.begin();
		//		 it_l != locations.end() ; it_l++)
		//	{
		//		std::cout << "\t\tLOCATION_BLOC (\'" << (*it_l).first << "\')" << std::endl;	
		//		const Parser::directiveMap locationDirectives = (*it_l).second.getDirectives();
		//		for (Parser::directiveConstIterator it_l_i = locationDirectives.begin() ;
		//			 it_l_i != locationDirectives.end() ; it_l_i++)
		//			std::cout << "\t\t" << (*it_l_i).first << " -> " << (*it_l_i).second << std::endl;
		//		std::cout << std::endl;
		//	}
		//	std::cout << std::endl;
		//}
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
