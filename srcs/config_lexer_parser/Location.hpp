/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:43 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 22:11:08 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "AContext.hpp"

const std::string locationPossibleDirectives[] = {"root", "index", ""}; //autoindex methodsrequetesdispo cgi
const std::string locationMandatoryDirectives[] = {"root", "index", ""};

class Location : public AContext {

public:
	#include "tools/LocationTypes.hpp"

	Location(const directiveMap &serverDirectives, const tokensVector &tokens, tokensConstIterator &it);
	~Location();

	const AContext::directiveMap	&getDirectives() const;

private:
	directiveMap	m_locationDirectives;

	void getLocationContext(const tokensVector &tokens, tokensConstIterator &it);

};

#endif
