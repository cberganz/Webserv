#include "ClientRequest.hpp"

ClientRequest::ClientRequest(): m_method(), m_path(), m_http_version(), m_body(), m_header()
{}

ClientRequest::ClientRequest(const ClientRequest &copy)
{
	if (this != &copy)
		*this = copy;
}

ClientRequest::~ClientRequest()
{}

ClientRequest  &ClientRequest::operator=(const ClientRequest &copy)
{
	if (this != &copy)
	{
		m_http_version = copy.m_http_version;
		m_method = copy.m_method;
		m_path = copy.m_path;
		m_header = copy.m_header;
		m_body = copy.m_body;
		m_query = copy.m_query;
	}
	return (*this);
}

/*
** Getter
*/

const std::string	ClientRequest::getPath() const
{ return (m_path); }

const std::string	ClientRequest::getMethod() const
{ return (m_method); }

const std::string	ClientRequest::getHttpVersion() const
{ return (m_http_version); }

const std::vector<char>	ClientRequest::getBody() const
{ return (m_body); }

const std::map<std::string, std::vector<std::string> >	ClientRequest::getHeader() const
{ return (m_header); }

const std::string	ClientRequest::getQuery() const
{ return (m_query); }

/*
** Setter
*/

void	ClientRequest::setPath(const std::string path)
{ m_path = path; }

void	ClientRequest::setMethod(const std::string method)
{ m_method = method; }

void	ClientRequest::setHttpVersion(const std::string http_version)
{ m_http_version = http_version; }

void	ClientRequest::setBody(const std::vector<char> body)
{ m_body = body; }

void	ClientRequest::setHeader(const std::map<std::string, std::vector<std::string> > header)
{ m_header = header; }

void	ClientRequest::setQuery(const std::string query)
{ m_query = query; }
