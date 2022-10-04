/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMaker.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:04:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/04 17:56:20 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseMaker.hpp"

ResponseMaker::ResponseMaker()
	: m_httpCodes(),
	  m_config(),
	  m_headerMaker(),
	  m_bodyMaker()
{}

ResponseMaker::ResponseMaker(const Config &config)
	: m_httpCodes(),
	  m_config(config),
	  m_headerMaker(),
	  m_bodyMaker()
{}

ResponseMaker::~ResponseMaker()
{}

ResponseMaker::ResponseMaker(const ResponseMaker &src)
{ *this = src; }

ResponseMaker& ResponseMaker::operator=(const ResponseMaker &rhs)
{
	if (this != &rhs)
	{
		this->m_httpCodes = rhs.m_httpCodes;
		this->m_config = rhs.m_config;
		this->m_headerMaker = rhs.m_headerMaker;
		this->m_bodyMaker = rhs.m_bodyMaker;
	}
	return *this;
}

Response* ResponseMaker::createResponse(const std::string &uri, const std::string &ip, const std::string &port)
{
	Response*	response = new Response();
	try {
		Context context = m_config[ip + ":" + port].getContext(uri); // WARNING: throw error if uri is not find in server. Throw HTTP error if this case ?
		std::string body = m_bodyMaker.createBody(context);
		(*response).append(m_headerMaker.createHeader());
		(*response).append(body);
	} catch (const std::out_of_range &e) {
		throw ErrorException(404);
	}
	return response;
}
