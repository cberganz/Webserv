/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:19:56 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/25 17:54:07 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
	: m_httpCode(200),
	m_response()
{}

Response::Response(const ClientRequest &client_req, const Context &context, const std::string &longest_location)
: m_httpCode(200), m_response(), m_path(), m_location(), m_context(context), m_client_req(client_req), m_isCGI(false)
{
	this->setPath(longest_location);
}


Response::~Response()
{}

Response::Response(const Response &src)
{ *this = src; }

Response &Response::operator=(const Response &rhs)
{
	if (this != &rhs)
	{
		this->m_response 	= rhs.m_response;
		this->m_httpCode 	= rhs.m_httpCode;
		this->m_path		= rhs.m_path;
		this->m_location	= rhs.m_location;
		this->m_context		= rhs.m_context;
		this->m_client_req	= rhs.m_client_req;
	}
	return *this;
}

const std::vector<char> &Response::getResponse() const
{ return m_response; }

const int	&Response::getHttpCode() const
{ return m_httpCode; }

const std::string	&Response::getPath() const
{ return m_path; }

const std::string	&Response::getLocation() const
{ return m_location; }

const Context	&Response::getContext() const
{ return m_context; }

const ClientRequest	&Response::getClientRequest() const
{ return m_client_req; }

bool Response::isCGI() const
{ return m_isCGI; }

void Response::append(const std::vector<char> &str)
{ this->m_response.insert(m_response.end(), str.begin(), str.end()); }

void Response::insert(size_t index, const std::string &str)
{
	this->m_response.insert(m_response.begin() + index, str.begin(), str.end());
}

void Response::setHttpCode(const int &code)
{ this->m_httpCode = code; }

void Response::setPath(const std::string &longest_location)
{
	std::string file_in_location = std::string(m_client_req.getPath()).erase(0, longest_location.length());

	m_path.clear();
	if (m_context.directiveExist("root"))
		m_path = *m_context.getDirective("root").begin();
	if (file_in_location.empty())
		m_path += "/" + *m_context.getDirective("index").begin();
	else
		m_path += "/" + file_in_location;
}

void Response::setContext(const Context &context)
{ this->m_context = context; }

void Response::setClientRequest(const ClientRequest &client_req)
{ this->m_client_req = client_req; }

void Response::setLocation(const std::string &location)
{ this->m_location = location; }

void Response::setCGI(bool isCGI)
{ this->m_isCGI = isCGI; }
