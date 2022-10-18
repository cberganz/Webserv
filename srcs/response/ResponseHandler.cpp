#include "ResponseHandler.hpp"

ResponseHandler::ResponseHandler()
: m_client_req_parser(), m_response_maker(), m_config()
{}

ResponseHandler::ResponseHandler(const Config &config)
: m_client_req_parser(), m_response_maker(config), m_config(config)
{}

ResponseHandler::ResponseHandler(const ResponseHandler &copy)
{
	if (this != &copy)
		*this = copy;
}

ResponseHandler::~ResponseHandler()
{}

ResponseHandler  &ResponseHandler::operator=(const ResponseHandler &copy)
{
	if (this != &copy)
	{
		m_client_req_parser	= copy.m_client_req_parser;
		m_response_maker	= copy.m_response_maker;
		m_config			= copy.m_config;
	}
	return (*this);
}

void	ResponseHandler::setClientRequest(std::vector<char> client_request)
{ m_client_req_parser.setRequest(client_request); }

std::string ResponseHandler::createResponseMessage(const std::string &ip, const std::string &port)
{
	ClientRequest	*client_req			= m_client_req_parser.makeClientRequest();
	client_req->print();
	Response		*response 			= m_response_maker.createResponse(*client_req, ip, port);
	std::string		response_message	= response->getResponse();

	delete client_req;
	delete response;
	return (response_message);
}
