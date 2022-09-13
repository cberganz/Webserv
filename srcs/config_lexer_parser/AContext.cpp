/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContext.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:02 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/13 10:31:24 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AContext.hpp"

AContext::AContext(const std::string &contextName)
	: m_contextName(contextName)
{}

AContext::~AContext()
{}

bool AContext::keywordExistsInContext(const std::string *context, const std::string &keyword)
{
	for (int i = 0 ; not context[i].empty() ; i++)
	{
		if (context[i] == keyword)
			return true;
	}
	return false;
}

bool AContext::checkMandatoryDirectives(const std::string *context, directiveMap &directives)
{
	for (int i = 0 ; not context[i].empty() ; i++)
	{
		directiveIterator it = directives.begin();
		while (it != directives.end())
		{
			if (context[i] == (*it).first)
				break;
			it++;
		}
		if (it == directives.end())
			return false;
	}
	return true;
}
