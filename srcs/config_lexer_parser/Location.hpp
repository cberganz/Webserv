/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:43 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 18:26:12 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "AContext.hpp"

const std::string locationPossibleDirectives[] = {"root", "index", ""};
const std::string locationMandatoryDirectives[] = {"root", "index", ""};

class AContext;

class Location : public AContext {

public:
	Location(const directiveMap &serverDirectives, const lexerVector &tokens, lexerIterator &it);
	~Location();

	const directiveMap	&getDirectives() const;

private:
	directiveMap	m_locationDirectives;

	void getLocationContext(const lexerVector &tokens, lexerIterator &it);

};

#endif
