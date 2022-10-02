/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderMaker.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:30:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/02 00:05:03 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeaderMaker.hpp"

HeaderMaker::fields HeaderMaker::m_fields[MAX_FIELDS];

HeaderMaker::HeaderMaker()
	: m_httpCodes()
{
	m_fields[0] = &HeaderMaker::date;
	m_fields[1] = &HeaderMaker::server;
	m_fields[2] = &HeaderMaker::location;
	m_fields[3] = &HeaderMaker::connection;
	m_fields[4] = &HeaderMaker::retry_after;
	m_fields[5] = &HeaderMaker::last_modified;
	m_fields[6] = &HeaderMaker::www_authenticate;
	m_fields[7] = &HeaderMaker::transfert_encoding;
	m_fields[8] = &HeaderMaker::content_type;
	m_fields[9] = &HeaderMaker::content_lenght;
	m_fields[10] = &HeaderMaker::content_location;
	m_fields[11] = &HeaderMaker::content_language;
}

HeaderMaker::HeaderMaker(const HeaderMaker &src)
{ *this = src; }

HeaderMaker::~HeaderMaker()
{}

HeaderMaker &HeaderMaker::operator=(const HeaderMaker &rhs)
{
	if (this != &rhs)
	{
		this->m_httpCodes = rhs.m_httpCodes;
		this->m_header = rhs.m_header;
		for (int i = 0 ; i < MAX_FIELDS ; i++)
			this->m_fields[i] = rhs.m_fields[i];
	}
	return *this;
}

std::string HeaderMaker::createHeader()
{
	m_header.clear();
	head();
	for (int i = 0 ; i < MAX_FIELDS ; i++)
	{
		if (headersTable[i].required)
		{
			m_header += headersTable[i].rowTitle + ": ";
			(this->*m_fields[i])();
			m_header += NEWLINE;
		}
	}
	return m_header;
}

void HeaderMaker::head()
{
	m_header += "HTTP/1.1";
	m_header += " " + ft::itostr(200); // TO_DO: code should come from request
	m_header += " " + m_httpCodes[200];// TO_DO: code should come from request
	m_header += NEWLINE;
}

void HeaderMaker::date()
{ m_header += ft::getTimeFormated(); }

void HeaderMaker::server()
{ m_header += "webserv-42"; }

void HeaderMaker::location()
{ m_header += ""; }

void HeaderMaker::connection()
{ m_header += ""; }

void HeaderMaker::retry_after()
{ m_header += "120"; }

void HeaderMaker::last_modified()
{ m_header += ""; }

void HeaderMaker::www_authenticate()
{ m_header += ""; }

void HeaderMaker::transfert_encoding()
{ m_header += ""; }

void HeaderMaker::content_type()
{ m_header += ""; }

void HeaderMaker::content_lenght()
{ m_header += ""; }

void HeaderMaker::content_location()
{ m_header += ""; }

void HeaderMaker::content_language()
{ m_header += ""; }
