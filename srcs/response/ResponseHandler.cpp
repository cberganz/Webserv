#include "ResponseHandler.hpp"

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
