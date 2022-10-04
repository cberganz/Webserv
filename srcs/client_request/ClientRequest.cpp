#include "ClientRequest.hpp"
# include "../tools/AsciiTable.hpp"

ClientRequest::ClientRequest(): m_method(), m_path(), m_http_version(), m_header(), m_body()
{}

ClientRequest::ClientRequest(std::string client_request): m_header()
{
	// check si string vide
	trimBegin(client_request, "\r\n");
	std::string					line;
	std::istringstream 			str_stream(client_request);
	std::vector<std::string>	key_value_vector;


	std::getline(str_stream, line);
	this->parse_request_line(line);
	this->replace_encode_char(m_path);
	if (!is_request_line_correct())
		throw ErrorException(400);
	client_request.erase(0, line.length() + 1); // verifier comportement si pas de \n a la fin
	this->parse_header(client_request);

	this->parse_body(client_request);
	this->print();
}

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
	}
	return (*this);
}

/*
** PRIVATE METHODS
*/

std::vector<std::string>	ClientRequest::tokenise(std::string str, char sep)
{
	std::vector<std::string>	token_vector;
	std::string					token;
	std::istringstream 			str_stream(str);

	while (getline(str_stream, token, sep))
	{
		token_vector.push_back(token);
		if (token.empty())
			throw ErrorException(400);
	}
	return (token_vector);
}

void	ClientRequest::parse_request_line(std::string request_line)
{
	std::string					*attributes[3] = {&m_method, &m_path, &m_http_version};
	std::istringstream 			str_stream(request_line);
	std::string					line;

	for (unsigned int i = 0; i < 3; i++)
	{
		getline(str_stream, line, ' ');
		if (line.empty() || !str_stream)
			throw ErrorException(400);
		*attributes[i] = line;
	}
	getline(str_stream, line);
	if (str_stream)
		throw ErrorException(400);
}

void	ClientRequest::parse_header(std::string str)
{
	std::string					line;
	std::istringstream 			str_stream(str);

	while (std::getline(str_stream, line))
	{
		this->trimBegin(line, "\n\r");
		if (line.empty())
			break ;
		if (line.find(':') == std::string::npos)
			throw ErrorException(400);
		
		std::istringstream	line_stream(line);
		std::string			header_key;
		std::string			header_value;

		getline(line_stream, header_key, ':');
		if (header_key.empty() || !str_stream || header_key.find(' ') != std::string::npos)
			throw ErrorException(400);
		getline(line_stream, header_value);
		if (header_value.empty() || !str_stream)
			throw ErrorException(400);
		this->trimBegin(header_value, " ");// trimer la value de tous les LWS(linear white space)
		this->trimEnd(header_value, " ");// trimer la value de tous les LWS(linear white space)
		m_header[header_key] = tokenise(header_value, ',');
	}
}

void	ClientRequest::parse_body(std::string str)
{
	std::string					line;
	int							header_length = 0;
	std::istringstream 			str_stream(str);

	while (std::getline(str_stream, line))
	{
		header_length += line.length() + 1;
		this->trimBegin(line, "\r");
		if (line.empty())
			break ;
	}
	str.erase(0, header_length);
	m_body = str;
}

void	ClientRequest::trimBegin(std::string &request, std::string charset)
{
	int last_new_line = 0;

	while (last_new_line < request.length()
			&& (charset.find(request[last_new_line]) != std::string::npos))
		last_new_line++;
	request.erase(0, last_new_line);
}

void	ClientRequest::trimEnd(std::string &request, std::string charset)
{
	int last_new_line = 0;

	for (size_t i = request.length() - 1; i >= 0; i--)
	{
		if (charset.find(request[i]) == std::string::npos)
			break ;
		last_new_line++;
	}
	request.erase(request.length() - last_new_line, last_new_line);
}

bool	ClientRequest::is_method_correct()
{
	std::string	accepted_methods[3] = {"GET", "POST", "DELETE"};

	for (int i = 0; i < 3; i++)
		if (m_method == accepted_methods[i])
			return (true);
	return (false);
}

bool	ClientRequest::is_path_correct()
{
	std::string	accepted_charset = "-._~!$&'()*+,;=:/";

	for (size_t i = 0; i < m_path.length(); i++)
		if (!isalnum(m_path[i])
			&& accepted_charset.find(m_path[i]) == std::string::npos)
			return (false);
	return (true);
}

bool	ClientRequest::is_http_version_correct()
{
	if (m_http_version != "HTTP/1.1")
		return (false);
	return (true);
}

bool	ClientRequest::is_request_line_correct()
{
	if (!is_method_correct()
		|| !is_path_correct()
		|| !is_http_version_correct())
		return (false);
	return (true);
}

void	ClientRequest::replace_encode_char(std::string &str)
{
	std::string	charset_to_replace;

	for (int i = 0; i < PRINTABLE_CHAR_COUNT; i++)
	{
		int pos = 0;
		charset_to_replace = "%" + printable_char[i].hexa_code;
		while ((pos = str.find(charset_to_replace, pos) ) != std::string::npos)
		{
			str.replace(pos, 3, 1, printable_char[i].c);
			pos++;
		}
	}
}

/*
** Getter
*/

std::string	ClientRequest::getPath() const
{ return (m_path); }

std::string	ClientRequest::getMethod() const
{ return (m_method); }

std::string	ClientRequest::getHttpVersion() const
{ return (m_http_version); }

std::string	ClientRequest::getBody() const
{ return (m_body); }

std::map<std::string, std::vector<std::string> >	ClientRequest::getHeader() const
{ return (m_header); }

/*
** To Delete
*/

void	ClientRequest::print()
{
	std::cout << "METHOD: " + m_method + "\n" + "PATH: " + m_path + "\n" + "VERSION: " + m_http_version << std::endl;
	std::cout << "\nHEADER:" << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = m_header.begin(); it != m_header.end(); it++)
	{
		std::cout << it->first << ": ";
		for (size_t i = 0; i < it->second.size(); i++)
			std::cout << it->second[i];
		std::cout << std::endl;
	}
	std::cout << "\n\nBody:\n" << m_body << std::endl;
}