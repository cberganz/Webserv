#include "ClientRequest.hpp"

ClientRequest::ClientRequest(): m_method(), m_path(), m_http_version(), m_header(), m_body()
{}

ClientRequest::ClientRequest(const std::string client_request): m_header()
{
	// check si string vide
	std::string					line;
	std::istringstream 			str_stream(client_request);
	std::vector<std::string>	key_value_vector;

	std::getline(str_stream, line);
	this->parse_request_line(line);//check retour getline


	while (std::getline(str_stream, line) && !line.empty()) // peut etre chercher des ':' avant de tokeniser
	{
		key_value_vector = tokenise(line, ':');
		if (m_header.find(key_value_vector[0]) == m_header.end())
			m_header[key_value_vector[0]] = tokenise(key_value_vector[1], ',');// trimer la value de tous les LWS(linear white space)
		else
		{
			std::vector<std::string>	new_content = tokenise(key_value_vector[1], ',');
			for (size_t i = 0; i < new_content.size(); i++)
				m_header[key_value_vector[0]].push_back(new_content[i]);
		}
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
	std::cout << "\n\n" << m_body << std::endl;
}