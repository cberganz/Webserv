/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/15 18:59:51 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <stdexcept>
# include "Context.hpp"

class Parser {

public:
	typedef std::vector<std::string>		tokensContainer;
	typedef tokensContainer::const_iterator	tokensIterator;
	typedef Context::directivesContainer	directivesContainer;
	typedef Context::directivesIterator		directivesIterator;
	typedef Context::contextsContainer		contextsContainer;
	typedef Context::contextsIterator		contextsIterator;

	Parser(const std::string &fileName);
	~Parser();

	const tokensContainer	&getTokens() const;
	const Context			&getGlobal() const;

private:
	tokensContainer	m_tokens;
	Context			m_global;

	std::string handleSpace(std::string::iterator &it);
	std::string handleCharToken(std::string::iterator &it);
	std::string handleComment(std::string::iterator &it);
	std::string handleVar(std::string::iterator &it);
	std::string handleKeyword(std::string::iterator &it);
	bool isKeyChar(const std::string::iterator &it) const;

	std::vector<std::string> readTokensFromFile(const std::string &filename);

	typedef std::string	(Parser::*func)(std::string::iterator &);
	typedef struct	s_funcPtr {
		std::string	pattern;
		func		ptr;
	} t_funcPtr;

};

#endif
