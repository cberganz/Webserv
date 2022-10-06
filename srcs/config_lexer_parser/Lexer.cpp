/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 18:00:44 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/06 02:58:19 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer()
{}

Lexer::Lexer(const Lexer &src)
{ *this = src; }

Lexer::Lexer(const std::string &fileName)
	: m_tokens(readTokensFromFile(fileName))
{}

Lexer::~Lexer()
{}

Lexer &Lexer::operator=(const Lexer &rhs)
{
	if (this != &rhs)
		m_tokens = rhs.m_tokens;
	return *this;
}

const std::vector<std::string> &Lexer::getTokens() const
{ return this->m_tokens; }

std::string Lexer::handleSpace(std::string::iterator &it)
{
	it++;
	return "";
}

std::string Lexer::handleCharToken(std::string::iterator &it)
{ return std::string(1, *it++); }

std::string Lexer::handleComment(std::string::iterator &it)
{
	while (*it != EOF and *it != '\n')
		it++;
	it++;
	return "";
}

std::string Lexer::handleVar(std::string::iterator &it)
{
	std::string tmp;
	tmp += *it++;
	while (*it != EOF
		   and not std::isspace(*it)
		   and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	return tmp;
}

std::string Lexer::handleQuoting(std::string::iterator &it)
{
	std::string tmp;
	char startChar = *it;
	it++;
	while (*it != EOF
		   and *it != startChar)
	{
		tmp += *it;
		it++;
	}
	it++;
	if (*it == EOF and *(it - 1) != startChar)
		throw std::invalid_argument("Parsing error: unclosed quotes in configuration file.");
	return tmp;
}

std::string Lexer::handleKeyword(std::string::iterator &it)
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

bool Lexer::isKeyChar(const std::string::iterator &it) const
{
	return (*it == ';'
		 or *it == '{'
		 or *it == '}'
		 or *it == '#'
		 or *it == '$');
}

std::vector<std::string> Lexer::readTokensFromFile(const std::string &fileName)
{
	std::string	line, save;
	Lexer::t_funcPtr funcPtrs[] =
	{
		{ std::string(" "),		&Lexer::handleSpace		},
		{ std::string("\t"),	&Lexer::handleSpace		},
		{ std::string("\f"), 	&Lexer::handleSpace		},
		{ std::string("\r"), 	&Lexer::handleSpace		},
		{ std::string("\v"), 	&Lexer::handleSpace		},
		{ std::string("\n"), 	&Lexer::handleCharToken	},
		{ std::string(";"),		&Lexer::handleCharToken	},
	    { std::string("{"),		&Lexer::handleCharToken	},
		{ std::string("}"),		&Lexer::handleCharToken	},
		{ std::string("\""),	&Lexer::handleQuoting	},
		{ std::string("\'"), 	&Lexer::handleQuoting	},
		{ std::string("#"),		&Lexer::handleComment	},
		{ std::string("$"),		&Lexer::handleVar		},
		{ std::string("EOA"),	&Lexer::handleKeyword	}
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
		for (int i = 0 ; i <= 13 ; i++)
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
