/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalContext.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:25 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/14 01:18:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALCONTEXT_HPP
# define GLOBALCONTEXT_HPP

# include "AContext.hpp"
# include "Server.hpp"

class GlobalContext : public AContext {

public:
	#include "tools/GlobalContextTypes.hpp"

	GlobalContext();
	GlobalContext(const tokensVector &tokens);
	~GlobalContext();

	const Server::serverMap			&getServers()	 const;
	const AContext::directiveMap	&getDirectives() const;

private:
	serverMap		m_servers;
	directiveMap	m_globalDirectives;

	void getGlobalContext(const tokensVector &tokens);

};

#endif
