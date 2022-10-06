/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 17:50:09 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/06 02:55:17 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <cctype>
# include <iomanip>
# include <fstream>
# include <string>
# include <stdexcept>
# include "Context.hpp"

# undef EOF
# define EOF '\0'

/*
**	@brief This lexer class is a configuration file tokenizer. It reads inputs
**		   from the configuration file and performs lexical analysis to insert
**		   tokens that were found inside a vector of tokens.
**	@category class
*/

class Lexer {

public:
	typedef std::vector<std::string>		tokensContainer;
	typedef tokensContainer::const_iterator	tokensIterator;

	Lexer();
	Lexer(const Lexer &src);
	Lexer(const std::string &fileName);
	~Lexer();

	Lexer &operator=(const Lexer &rhs);

	const tokensContainer &getTokens() const;

private:
	tokensContainer	m_tokens;

	std::string handleSpace(std::string::iterator &it);
	std::string handleNewline(std::string::iterator &it);
	std::string handleCharToken(std::string::iterator &it);
	std::string handleComment(std::string::iterator &it);
	std::string handleVar(std::string::iterator &it);
	std::string handleQuoting(std::string::iterator &it);
	std::string handleKeyword(std::string::iterator &it);

	bool isKeyChar(const std::string::iterator &it) const;

	std::vector<std::string> readTokensFromFile(const std::string &filename);

	typedef std::string	(Lexer::*func)(std::string::iterator &);
	typedef struct	s_funcPtr {
		std::string	pattern;
		func		ptr;
	} t_funcPtr;

};

#endif
