/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:30 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 11:43:18 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser(const std::string &fileName)
{
	getTokens(fileName);
	m_globalContext = GlobalContext(m_tokens);
}

Parser::~Parser()
{}

const std::vector<std::string> &Parser::getTokens()
{ return this->m_tokens; }

const GlobalContext &Parser::getGlobal()
{ return this->m_globalContext; }

void Parser::handleSpace(std::string::iterator &it)
{ it++; }

void Parser::handleCharToken(std::string::iterator &it)
{
	std::string tmp;
	tmp += *it;
	m_tokens.push_back(tmp);
	it++;
}

void Parser::handleComment(std::string::iterator &it)
{
	while (*it != '\0' and *it != '\n')
		it++;
	it++;
}

void Parser::handleVar(std::string::iterator &it)
{
	std::string tmp;
	while (*it != '\0' and not std::isspace(*it) and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	m_tokens.push_back(tmp);
}

void Parser::handleKeyword(std::string::iterator &it)
{
	std::string tmp;
	while (*it != '\0'
		   and not std::isspace(*it)
		   and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	m_tokens.push_back(tmp);
}

bool Parser::isKeyChar(const std::string::iterator &it) const
{
	return (*it == ';'
		 or *it == '{'
		 or *it == '}'
		 or *it == '#'
		 or *it == '$');
}

void Parser::getTokens(const std::string &fileName)
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
		throw std::invalid_argument("File not found or can't be opened.");
	while (std::getline(fileIn, line))
		save.append(line.append("\n"));
	std::string::iterator it = save.begin();
	while (*it != '\0')
	{
		for (int i = 0 ; i <= 11 ; i++)
		{
			if (*it == funcPtrs[i].pattern[0] || funcPtrs[i].pattern == "EOA")
			{
				(this->*funcPtrs[i].ptr)(it);
				break;
			}
		}
	}
}
