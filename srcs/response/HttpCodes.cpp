/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCodes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:54:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/22 16:39:49 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpCodes.hpp"

HttpCodes::HttpCodes()
{
	m_codes[100]="Continue";
	m_codes[101]="Switching Protocols";
	m_codes[102]="Processing";
	m_codes[103]="Early Hints";
	m_codes[200]="OK";
	m_codes[201]="Created";
	m_codes[202]="Accepted";
	m_codes[203]="Non-Authoritative Information";
	m_codes[204]="No Content";
	m_codes[205]="Reset Content";
	m_codes[206]="Partial Content";
	m_codes[207]="Multi-Status";
	m_codes[208]="Already Reported";
	m_codes[210]="Content Different";
	m_codes[226]="IM Used";
	m_codes[300]="Multiple Choices";
	m_codes[301]="Moved Permanently";
	m_codes[302]="Found";
	m_codes[303]="See Other";
	m_codes[304]="Not Modified";
	m_codes[305]="Use Proxy (depuis HTTP/1.1)";
	m_codes[306]="Switch Proxy";
	m_codes[307]="Temporary Redirect";
	m_codes[308]="Permanent Redirect";
	m_codes[310]="Too many Redirects";
	m_codes[400]="Bad Request";
	m_codes[401]="Unauthorized";
	m_codes[402]="Payment Required";
	m_codes[403]="Forbidden";
	m_codes[404]="Not Found";
	m_codes[405]="Method Not Allowed";
	m_codes[406]="Not Acceptable";
	m_codes[407]="Proxy Authentication Required";
	m_codes[408]="Request Time-out";
	m_codes[409]="Conflict";
	m_codes[410]="Gone";
	m_codes[411]="Length Required";
	m_codes[412]="Precondition Failed";
	m_codes[413]="Request Entity Too Large";
	m_codes[414]="Request-URI Too Long";
	m_codes[415]="Unsupported Media Type";
	m_codes[416]="Requested range unsatisfiable";
	m_codes[417]="Expectation failed";
	m_codes[418]="I’m a teapot";
	m_codes[421]="Bad mapping / Misdirected Request";
	m_codes[422]="Unprocessable entity";
	m_codes[423]="Locked";
	m_codes[424]="Method failure";
	m_codes[425]="Too Early";
	m_codes[426]="Upgrade Required";
	m_codes[428]="Precondition Required";
	m_codes[429]="Too Many Requests";
	m_codes[431]="Request Header Fields Too Large";
	m_codes[449]="Retry With";
	m_codes[450]="Blocked by Windows Parental Controls";
	m_codes[451]="Unavailable For Legal Reasons";
	m_codes[456]="Unrecoverable Error";
	m_codes[500]="Internal Server Error";
	m_codes[501]="Not Implemented";
	m_codes[502]="Bad Gateway ou Proxy Error";
	m_codes[503]="Service Unavailable";
	m_codes[504]="Gateway Time-out";
	m_codes[505]="HTTP Version not supported";
	m_codes[506]="Variant Also Negotiates";
	m_codes[507]="Insufficient storage";
	m_codes[508]="Loop detected";
	m_codes[509]="Bandwidth Limit Exceeded";
	m_codes[510]="Not extended";
	m_codes[511]="Network authentication required";
}

HttpCodes::HttpCodes(const HttpCodes &src)
{ *this = src; }

HttpCodes::~HttpCodes()
{}

HttpCodes &HttpCodes::operator=(const HttpCodes &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0 ; i <= MAX_CODE ; i++)
			this->m_codes[i] = rhs.m_codes[i];
	}
	return *this;
}

bool HttpCodes::codeExist(int code) const
{
	if (code < 0 or code > MAX_CODE or m_codes[code].empty())
		return false;
	return true;
}

const std::string &HttpCodes::operator[](int code) const
{
	if (code < 0 or code > MAX_CODE or m_codes[code].empty())
		throw InvalidCodeException();
	return m_codes[code];
}

HttpCodes::InvalidCodeException::InvalidCodeException()
	: message("Error while reading from HttpCode table: Code does not exist.")
{}

HttpCodes::InvalidCodeException::~InvalidCodeException() throw()
{}

const char* HttpCodes::InvalidCodeException::what() const throw()
{ return message.c_str(); }
