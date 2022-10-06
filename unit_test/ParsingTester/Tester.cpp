/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:18 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/06 01:56:01 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include "../../srcs/config_lexer_parser/Config.hpp"

void printTab(int tabCount)
{
	for (int i = 0 ; i < tabCount ; i++)
		std::cout << "\t";
}

void printDirectives(const Config::directivesContainer &directives, int tabCount)
{
	for (Config::directivesContainer::const_iterator it = directives.begin() ;
		 it != directives.end() ; it++)
	{
		printTab(tabCount);
		std::cout << (*it).first << " ->";
		for (std::vector<std::string>::const_iterator it_vec = (*it).second.begin() ; it_vec != (*it).second.end() ; it_vec ++)
			std::cout << " " << *it_vec << std::endl;
	}
	std::cout << std::endl;
}

void RContextsContainer(const Config::contextsContainer &contexts, int tabCount)
{
	for (Config::contextsContainer::const_iterator it = contexts.begin() ;
		 it != contexts.end() ; it++)
	{
		printTab(tabCount);
		std::cout << "[" << (*it).second.getContextName() << "]"
				  << "[" << (*it).first << "]" << std::endl;
		printDirectives((*it).second.getDirectives(), tabCount);
		if (not (*it).second.getContexts().empty())
			RContextsContainer((*it).second.getContexts(), tabCount + 1);
	}
}

int main(int argc, char *argv[])
{
	std::string path = "default.conf";
	if (argc == 2)
		path = argv[1];
	else if (argc > 2)
	{
		std::cout << "Too many arguments." << std::endl;
		return 1;
	}
	try {
		Config config(path);
		//std::cout << "TEST: " << config["443"].getDirective("server_name") << std::endl;
		Config::contextsContainer cont;
		cont.insert(std::make_pair("global", config.getParser().getRoot()));
		RContextsContainer(cont, 0);
	} catch(const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
