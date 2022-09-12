/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 11:10:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>

class Lexer {

public:
	typedef std::vector<std::string>	vector;
	typedef vector::iterator			iterator;

	Lexer(const std::string &fileName);
	~Lexer();

	iterator begin();
	iterator end();

private:
	Lexer::vector	m_tokens;
	std::string		m_fileName;

	void handleSpace(std::string::iterator &it);
	void handleCharToken(std::string::iterator &it);
	void handleComment(std::string::iterator &it);
	void handleVar(std::string::iterator &it);
	void handleKeyword(std::string::iterator &it);
	bool isKeyChar(const std::string::iterator &it) const;

	bool getTokens();

	typedef void	(Lexer::*func)(std::string::iterator &);
	typedef struct	s_funcPtr
	{
		std::string	pattern;
		func		ptr;
	} t_funcPtr;

};

#endif
