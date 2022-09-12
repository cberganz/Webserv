/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:11:00 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 18:25:57 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "AContext.hpp"

const std::string serverPossibleDirectives[] = {"root", "listen", "server_name", ""};
const std::string serverMandatoryDirectives[] = {"root", "listen", "server_name", ""};
const std::string serverPossibleBlocs[] = {"location", ""};

class AContext;

class Server : public AContext {

public:
	Server(const directiveMap &globalDirectives, const lexerVector &tokens, lexerIterator &it);
	~Server();

	const locationMap	&getlocations() const;
	const directiveMap	&getDirectives() const;

private:
	locationMap		m_locations;
	directiveMap	m_serverDirectives;

	void getServerContext(const lexerVector &tokens, lexerIterator &it);

};

#endif
