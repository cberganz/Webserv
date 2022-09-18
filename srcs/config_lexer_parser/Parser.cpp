/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/17 18:39:54 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::string &fileName)
	: m_tokens(readTokensFromFile(fileName)),
	  m_global(m_tokens)
{}

Parser::~Parser()
{}

const std::vector<std::string> &Parser::getTokens() const
{ return this->m_tokens; }

const Context &Parser::getGlobal() const
{ return this->m_global; }

std::string Parser::handleSpace(std::string::iterator &it)
{
	it++;
	return "";
}

std::string Parser::handleCharToken(std::string::iterator &it)
{ return std::string(1, *it++); }

std::string Parser::handleComment(std::string::iterator &it)
{
	while (*it != EOF and *it != '\n')
		it++;
	it++;
	return "";
}

std::string Parser::handleVar(std::string::iterator &it)
{
	std::string tmp;
	while (*it != EOF and not std::isspace(*it) and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	return tmp;
}

std::string Parser::handleKeyword(std::string::iterator &it)
{
	std::string tmp;
	while (*it != EOF
		   and not std::isspace(*it)
		   and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	return tmp;
}

bool Parser::isKeyChar(const std::string::iterator &it) const
{
	return (*it == ';'
		 or *it == '{'
		 or *it == '}'
		 or *it == '#'
		 or *it == '$');
}

std::vector<std::string> Parser::readTokensFromFile(const std::string &fileName)
{
	std::string	line, save;
	Parser::t_funcPtr funcPtrs[] =
	{
		{std::string(" "), &Parser::handleSpace},
		{std::string("\t"), &Parser::handleSpace},
		{std::string("\f"), &Parser::handleSpace},
		{std::string("\n"), &Parser::handleSpace},
		{std::string("\r"), &Parser::handleSpace},
		{std::string("\v"), &Parser::handleSpace},
		{std::string(";"), &Parser::handleCharToken},
	    {std::string("{"), &Parser::handleCharToken},
		{std::string("}"), &Parser::handleCharToken},
		{std::string("#"), &Parser::handleComment},
		{std::string("$"), &Parser::handleVar},
		{std::string("EOA"), &Parser::handleKeyword}
	};

	std::ifstream fileIn(fileName.c_str());
	if (!fileIn)
		throw std::invalid_argument("\'" + fileName + "\': File not found or can't be opened.");
	while (std::getline(fileIn, line))
		save.append(line + "\n");

	std::vector<std::string> tokens;
	std::string::iterator it = save.begin();
	while (*it != EOF)
	{
		for (int i = 0 ; i <= 11 ; i++)
		{
			if (*it == funcPtrs[i].pattern[0] || funcPtrs[i].pattern == "EOA")
			{
				std::string tmp((this->*funcPtrs[i].ptr)(it));
				if (not tmp.empty())
					tokens.push_back(tmp);
				break;
			}
		}
	}
	tokens.push_back("");
	return tokens;
}
