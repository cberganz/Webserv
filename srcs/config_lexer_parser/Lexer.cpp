#include "Lexer.hpp"

Lexer::Lexer(const std::string &fileName)
	: m_fileName(fileName)
{
	this->getTokens();
}

Lexer::~Lexer()
{

}

Lexer::iterator Lexer::begin()
{
	return m_tokens.begin();
}

Lexer::iterator Lexer::end()
{
	return m_tokens.end();
}

void Lexer::handleSpace(std::string::iterator &it)
{
	it++;
}

void Lexer::handleCharToken(std::string::iterator &it)
{
	std::string tmp;
	tmp += *it;
	m_tokens.push_back(tmp);
	it++;
}

void Lexer::handleComment(std::string::iterator &it)
{
	while (*it != '\0' and *it != '\n')
		it++;
	it++;
}

void Lexer::handleVar(std::string::iterator &it)
{
	std::string tmp;
	while (*it != '\0' and not std::isspace(*it) and not isKeyChar(it))
	{
		tmp += *it;
		it++;
	}
	m_tokens.push_back(tmp);
}

void Lexer::handleKeyword(std::string::iterator &it)
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

bool Lexer::isKeyChar(const std::string::iterator &it) const
{
	return (*it == ';'
			or *it == '{' or *it == '}' or *it == '#' or *it == '$');
}

bool	Lexer::getTokens(void)
{
	std::string				line, save;
	Lexer::t_funcPtr funcPtrs[] =
	{
		{std::string(" "), &Lexer::handleSpace},
		{std::string("\t"), &Lexer::handleSpace},
		{std::string("\f"), &Lexer::handleSpace},
		{std::string("\n"), &Lexer::handleSpace},
		{std::string("\r"), &Lexer::handleSpace},
		{std::string("\v"), &Lexer::handleSpace},
		{std::string(";"), &Lexer::handleCharToken},
	    {std::string("{"), &Lexer::handleCharToken},
		{std::string("}"), &Lexer::handleCharToken},
		{std::string("#"), &Lexer::handleComment},
		{std::string("$"), &Lexer::handleVar},
		{std::string("EOA"), &Lexer::handleKeyword}
	};

	std::ifstream fileIn(this->m_fileName.c_str());
	if (!fileIn)
		return (false);
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
	return (true);
}
