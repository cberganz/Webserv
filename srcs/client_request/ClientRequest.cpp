#include "ClientRequest.hpp"

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
	this->parse_request_line(line);//check retour getline

	while (std::getline(str_stream, line)) // peut etre chercher des ':' avant de tokeniser
	{
		this->trimNewLine(line);		
		if (line.empty())
			break ;
		// if (line.find(':') == std::string::npos)
			// throw Error(400);
		key_value_vector = tokenise(line, ':');
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
		std::getline(str_stream, line, ' ');// checker erreurs sur getline
		*attributes[i] = line;
	}
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
	std::cout << m_method + " " + m_path + " " + m_http_version << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = m_header.begin(); it != m_header.end(); it++)
	{
		std::cout << it->first << ": ";
		for (size_t i = 0; i < it->second.size(); i++)
			std::cout << it->second[i];
		std::cout << std::endl;
	}
	std::cout << "\n\nBody:\n\n" << m_body << std::endl;
}