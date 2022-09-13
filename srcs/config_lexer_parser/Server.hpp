/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:11:00 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 22:16:23 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "AContext.hpp"
# include "Location.hpp"

const std::string serverPossibleDirectives[] = {"root", "listen", "server_name", "index", ""};
const std::string serverMandatoryDirectives[] = {"root", "listen", "server_name", ""}; //server name pas oblig?
const std::string serverPossibleBlocs[] = {"location", ""};

class Server : public AContext {

public:
	#include "tools/ServerTypes.hpp"

	Server(const directiveMap &globalDirectives,
		   const tokensVector &tokens,
		   tokensConstIterator &it);
	~Server();

	const Location::locationMap		&getLocations() const;
	const AContext::directiveMap	&getDirectives() const;

private:
	Location::locationMap	m_locations;
	directiveMap			m_serverDirectives;

	void getServerContext(const tokensVector &tokens, tokensConstIterator &it);

};

#endif
