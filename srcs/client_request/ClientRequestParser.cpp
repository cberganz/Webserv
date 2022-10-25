#include "ClientRequestParser.hpp"
# include "../tools/AsciiTable.hpp"

ClientRequestParser::ClientRequestParser(): m_request()
{}

ClientRequestParser::ClientRequestParser(std::vector<char> client_request): m_request(client_request)
{}

ClientRequestParser::ClientRequestParser(const ClientRequestParser &copy)
{
	if (this != &copy)
		*this = copy;
}

ClientRequestParser::~ClientRequestParser()
{}

ClientRequestParser  &ClientRequestParser::operator=(const ClientRequestParser &copy)
{
	if (this != &copy)
	{
		m_request = copy.m_request;
	}
	return (*this);
}

/*
** PRIVATE METHODS
*/

std::vector<std::string>	ClientRequestParser::tokenise(std::string str, char sep)
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

void	ClientRequestParser::parse_request_line(std::string request_line, ClientRequest &client_req)
{
	std::string					attributes[3];
	std::istringstream 			str_stream(request_line);
	std::string					line;

	for (unsigned int i = 0; i < 3; i++)
	{
		getline(str_stream, line, ' ');
		if (line.empty() || !str_stream)
			throw ErrorException(400);
		attributes[i] = line;
	}
	getline(str_stream, line);
	if (str_stream)
		throw ErrorException(400);
	this->replace_encode_char(attributes[1]);
	client_req.setMethod(attributes[0]);
	if (attributes[1].find('?', 0) != std::string::npos)
	{
		client_req.setPath(this->strToLower(std::string(attributes[1].begin(),
			attributes[1].begin() + attributes[1].find('?', 0))));
		std::cout << "\n\nTEST PATH: " + client_req.getPath() + "\n";
		client_req.setQuery(std::string(attributes[1].begin() + attributes[1].find('?', 0) + 1,
			attributes[1].end()));
	}
	else
	{
		client_req.setPath(attributes[1]);
		client_req.setQuery(std::string());
	}
	client_req.setHttpVersion(attributes[2]);
}

std::string	ClientRequestParser::strToLower(std::string str)
{
	std::string copy(str);

	for (std::string::iterator it = copy.begin(); it != copy.end(); it++)
		*it = std::tolower(*it);
	return (copy);
}

std::map<std::string, std::vector<std::string> >	ClientRequestParser::parse_header(std::string str)
{
	std::string											line;
	std::istringstream 									str_stream(str);
	std::map<std::string, std::vector<std::string> >	header;

	
	while (std::getline(str_stream, line, '\r'))
	{
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
		this->trimBegin(header_value, " \f\t\n\r\v");
		this->trimEnd(header_value, " \f\t\n\r\v");
		header[strToLower(header_key)] = tokenise(header_value, ',');
		std::getline(str_stream, line);
	}
	return (header);
}

std::vector<char>	ClientRequestParser::parse_body(std::vector<char> str)
{
	int	start_body = ft::search_vector_char(str, "\r\n\r\n", 0) + 4;
	str.erase(str.begin(), str.begin() + start_body);
	return (str);
}

void	ClientRequestParser::trimBegin(std::string &request, std::string charset)
{
	size_t last_new_line = 0;

	while (last_new_line < request.length()
			&& (charset.find(request[last_new_line]) != std::string::npos))
		last_new_line++;
	request.erase(0, last_new_line);
}

void	ClientRequestParser::trimEnd(std::string &request, std::string charset)
{
	int last_new_line = 0;

	for (int i = static_cast<int>(request.length() - 1); i >= 0; i--)
	{
		if (charset.find(request[i]) == std::string::npos)
			break ;
		last_new_line++;
	}
	request.erase(request.length() - last_new_line, last_new_line);
}

bool	ClientRequestParser::is_path_correct(std::string path)
{
	std::string	accepted_charset = "-._~!$&'()*+,;=:/";

	for (size_t i = 0; i < path.length(); i++)
		if (!isalnum(path[i])
			&& accepted_charset.find(path[i]) == std::string::npos)
			return (false);
	return (true);
}

bool	ClientRequestParser::is_http_version_correct(std::string http_version)
{
	if (http_version != "HTTP/1.1")
		return (false);
	return (true);
}

bool	ClientRequestParser::is_request_line_correct(ClientRequest client_req)
{
	if (!is_path_correct(client_req.getPath())
		|| !is_http_version_correct(client_req.getHttpVersion()))
		return (false);
	return (true);
}

void	ClientRequestParser::replace_encode_char(std::string &str)
{
	std::string	charset_to_replace;

	for (int i = 0; i < PRINTABLE_CHAR_COUNT; i++)
	{
		size_t pos = 0;
		charset_to_replace = "%" + printable_char[i].hexa_code;
		while ((pos = str.find(charset_to_replace, pos) ) != std::string::npos)
		{
			str.replace(pos, 3, 1, printable_char[i].c);
			pos++;
		}
	}
}

std::string	ClientRequestParser::getStringHeader()
{
	std::string	request_string(m_request.begin(), m_request.end());

	request_string = request_string.substr(0, request_string.find("\r\n\r\n"));
	trimBegin(request_string, "\r\n");
	return (request_string);
}

/*
** PUBLIC METHODS
*/

ClientRequest	ClientRequestParser::makeClientRequest()
{
	std::string			request_string = getStringHeader();
	std::string			line;
	std::istringstream 	str_stream(request_string);
	ClientRequest		client_req;

	std::getline(str_stream, line);
	trimEnd(line, "\r\n");
	parse_request_line(line, client_req);

	if (!is_request_line_correct(client_req))
		throw ErrorException(400);
	request_string.erase(0, line.length());
	trimBegin(request_string, "\r\n");
	client_req.setHeader(parse_header(request_string));
	client_req.setBody(parse_body(m_request));
	return (client_req);
}

void	ClientRequestParser::setRequest(const std::vector<char> request)
{ m_request = request; }
