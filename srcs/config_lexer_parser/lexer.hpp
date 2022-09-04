#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>

class Lexer {

private:
	std::vector<std::string>	m_tokens;
	std::string					m_fileString;

	void readFile();
	void tokenize();

public:
	Lexer(const std::string &fileName);
	~Lexer();

	const std::string &getToken(

};

#endif
