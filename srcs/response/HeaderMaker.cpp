/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderMaker.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:30:57 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 05:55:00 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HeaderMaker.hpp"

HeaderMaker::conditions HeaderMaker::m_conditions[MAX_FIELDS];
HeaderMaker::fields		HeaderMaker::m_fields[MAX_FIELDS];

HeaderMaker::HeaderMaker()
	: m_httpCodes()
{
	m_conditions[0] = &HeaderMaker::condition_date;
	m_conditions[1] = &HeaderMaker::condition_server;
	m_conditions[2] = &HeaderMaker::condition_location;
	m_conditions[3] = &HeaderMaker::condition_connection;
	m_conditions[4] = &HeaderMaker::condition_retry_after;
	m_conditions[5] = &HeaderMaker::condition_last_modified;
	m_conditions[6] = &HeaderMaker::condition_www_authenticate;
	m_conditions[7] = &HeaderMaker::condition_transfert_encoding;
	m_conditions[8] = &HeaderMaker::condition_content_type;
	m_conditions[9] = &HeaderMaker::condition_content_lenght;
	m_conditions[10] = &HeaderMaker::condition_content_location;
	m_conditions[11] = &HeaderMaker::condition_content_language;
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
		if ((this->*m_conditions[i])())
		{
			m_header += headersTable[i].rowTitle + ": ";
			(this->*m_fields[i])();
			m_header += NEWLINE;
		}
	}
	m_header += NEWLINE;
	return m_header;
}

void HeaderMaker::head()
{
	m_header += "HTTP/1.1";
	m_header += " " + ft::itostr(200); // TO_DO: code should come from request
	m_header += " " + m_httpCodes[200];// TO_DO: code should come from request
	m_header += NEWLINE;
}

bool HeaderMaker::condition_date()
{ return true; }

bool HeaderMaker::condition_server()
{ return true; }

bool HeaderMaker::condition_location()
{ return false; }

bool HeaderMaker::condition_connection()
{ return false; }

bool HeaderMaker::condition_retry_after()
{ return true; }

bool HeaderMaker::condition_last_modified()
{ return false; }

bool HeaderMaker::condition_www_authenticate()
{ return false; }

bool HeaderMaker::condition_transfert_encoding()
{ return true; }

bool HeaderMaker::condition_content_type()
{ return true; }

bool HeaderMaker::condition_content_lenght()
{ return false; }

bool HeaderMaker::condition_content_location()
{ return false; }

bool HeaderMaker::condition_content_language()
{ return false; }

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
{ m_header += "chunked"; }

void HeaderMaker::content_type()
{ m_header += "text/html; charset=utf-8"; }

void HeaderMaker::content_lenght()
{ m_header += ""; }

void HeaderMaker::content_location()
{ m_header += ""; }

void HeaderMaker::content_language()
{ m_header += ""; }
