/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 05:11:23 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <string>
# include "Context.hpp"
# include "Lexer.hpp"

/*
**	@brief This class is a bridge between Lexer and Context classes. Its role
**		   is to supervise the parsing of the configuration file. It also has
**		   the responsibility about variable expansions etc. once the configuration
**		   file has been parsed onto a composite three.
**
**	@TODO: IN PROGRESS... Please come back later.
*/

class Parser : public Lexer {

public:
	using typename Lexer::tokensContainer;
	using typename Lexer::tokensIterator;

	typedef Context::directivesContainer		directivesContainer;
	typedef Context::directivesIterator			directivesIterator;
	typedef Context::directivesConstIterator	directivesConstIterator;
	typedef Context::contextsContainer			contextsContainer;
	typedef Context::contextsIterator			contextsIterator;
	typedef Context::contextsConstIterator		contextsConstIterator;

	Parser();
	Parser(const Parser &src);
	Parser(const std::string &fileName);
	~Parser();

	Parser &operator=(const Parser &rhs);

	const Context &getRoot() const;

private:
	Context	m_root;

	void checkMandatories(Context &context);
	void setServersIpsAndPorts(Context &context);

};

#endif
