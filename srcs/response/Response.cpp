/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:19:56 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 05:41:07 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response()
	: m_response(),
	  m_httpCode(200)
{}

Response::~Response()
{}

Response::Response(const Response &src)
{ *this = src; }

Response &Response::operator=(const Response &rhs)
{
	if (this != &rhs)
	{
		this->m_response = rhs.m_response;
		this->m_httpCode = rhs.m_httpCode;
	}
	return *this;
}

const std::string &Response::getResponse()
{ return m_response; }

void Response::append(const std::string &str)
{ this->m_response += str; }

void Response::setHttpCode(const int &code)
{ this->m_httpCode = code; }
