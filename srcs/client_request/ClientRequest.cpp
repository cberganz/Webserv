#include "ClientRequest.hpp"
# include "../tools/AsciiTable.hpp"

ClientRequest::ClientRequest(): m_method(), m_path(), m_http_version(), m_header(), m_body()
{}

ClientRequest::ClientRequest(std::string client_request): m_header()
{
	// check si string vide
	trimNewLine(client_request);
	std::string					line;
	std::istringstream 			str_stream(client_request);
	std::vector<std::string>	key_value_vector;


	std::getline(str_stream, line);
	this->parse_request_line(line);
	this->replace_encode_char(m_path);
	if (!is_request_line_correct())
		throw ErrorException(400);

	while (std::getline(str_stream, line))
	{
		this->trimNewLine(line);		
		if (line.empty())
			break ;
		if (line.find(':') == std::string::npos)
			throw ErrorException(400);
		key_value_vector = tokenise(line, ':');
		if (key_value_vector.size() != 2
			|| key_value_vector[1].empty()
			|| key_value_vector[0].find(' ') == std::string::npos)
			throw ErrorException(400);
		m_header[key_value_vector[0]] = tokenise(key_value_vector[1], ',');// trimer la value de tous les LWS(linear white space)
	}
	if (std::getline(str_stream, line))
		m_body = line;
	else
		m_body = "";
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
	size_t						begin, end = 0;

	while ((begin = str.find_first_not_of(sep, end)) != std::string::npos)
	{
		end = str.find(sep, begin);
		token_vector.push_back(str.substr(begin, end - begin));
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
		getline(str_stream, line, ' ');// checker erreurs sur getline
		if (line.empty() || !str_stream)
			throw ErrorException(400);
		*attributes[i] = line;
	}
	getline(str_stream, line);
	if (str_stream)
		throw ErrorException(400);
}

void	ClientRequest::trimNewLine(std::string &request)
{
	int last_new_line = 0;

	while (last_new_line < request.length()
			&& (request[last_new_line] == '\n'
			|| request[last_new_line] == '\r'))
		last_new_line++;
	request.erase(0, last_new_line);
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
	for (std::map<std::string, std::vector<std::string> >::iterator it = m_header.begin(); it != m_header.end(); it++)
	{
		std::cout << it->first << ": ";
		for (size_t i = 0; i < it->second.size(); i++)
			std::cout << it->second[i];
		std::cout << std::endl;
	}
	std::cout << "\n\nBody:\n\n" << m_body << std::endl;
}