/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:25 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 18:25:51 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALCONTEXT_HPP
# define GLOBALCONTEXT_HPP

# include "AContext.hpp"

const std::string globalDirectives[] = {"root", ""};
const std::string globalPossibleBlocs[] = {"server", ""};

class AContext;

class GlobalContext : public AContext {

public:
	GlobalContext(const Lexer &lexer);
	~GlobalContext();

	const serverMap		&getServers() const;
	const directiveMap	&getDirectives() const;

private:
	serverMap		m_servers;
	directiveMap	m_globalDirectives;

	void getGlobalContext(const Lexer &lexer);

};

#endif
