/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:34 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/30 04:02:48 by cberganz         ###   ########.fr       */
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

class Parser : public Context {

public:
	using typename Context::tokensContainer;
	using typename Context::tokensIterator;
	using typename Context::directivesContainer;
	using typename Context::directivesIterator;
	using typename Context::directivesConstIterator;
	using typename Context::contextsContainer;
	using typename Context::contextsIterator;
	using typename Context::contextsConstIterator;

	Parser();
	Parser(const Parser &src);
	Parser(const std::string &fileName);
	~Parser();

	Parser &operator=(const Parser &rhs);

private:
	Lexer	m_lexer;

	void checkMandatories(Context &context);
	void setServersIpsAndPorts(Context &context);

};

#endif
