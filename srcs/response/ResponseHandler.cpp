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

void	ResponseHandler::setClientRequest(const std::vector<char> client_request)
{ m_client_req_parser.setRequest(client_request); }

void	ResponseHandler::handleErrorPageDirective(const Context &context, int error_status, const std::string path)
{
	ContextBase::tokensContainer error_page_tokens =
			context.getDirective("error_page");

	if (error_page_tokens.front() == "default")
		throw ErrorException(error_status);

	Lexer::tokensContainer::iterator error_it =
				std::find(error_page_tokens.begin(), error_page_tokens.end(), ft::itostr(error_status));

	if (error_it == error_page_tokens.end()
		|| error_it + 1 == error_page_tokens.end())
			throw ErrorException(error_status);

	std::string error_file_path = path + "/" + *(error_it + 1);

	if (access(error_file_path.c_str(), F_OK ) != -1
		&& access(error_file_path.c_str(), R_OK ) != -1)
			throw ErrorException(error_status, error_file_path);

	throw ErrorException(error_status);
}

std::string	ResponseHandler::findLongestLocation(const Context& context, std::string uri)
{
	while (!uri.empty())
	{
		if (context.contextExist(uri))
			return (uri);
		if (uri[uri.size() - 1] == '/')
			uri = uri.erase(uri.find_last_of("/"), uri.length() - uri.find_last_of("/"));
		else
			uri = uri.erase(uri.find_last_of("/") + 1, uri.length() - uri.find_last_of("/"));
	}
	if (context.contextExist("/"))
		return ("/");
	return (uri);
}

std::vector<char> ResponseHandler::createResponseMessage(const std::string &ip, const std::string &port)
{
	Context 		server;
	ClientRequest 	client_req;
	std::string 	longest_location;

	try {
		client_req = m_client_req_parser.makeClientRequest();

		if (client_req.getHeader().find("host") == client_req.getHeader().end())
			server = m_config.getServer(ip, port);
		else
			server = m_config.getServer(ip, port, *client_req.getHeader().at("host").begin());
		longest_location = findLongestLocation(server, client_req.getPath());

		Response				response 			= m_response_maker.createResponse(client_req, server, longest_location);
		std::vector<char>		response_message	= response.getResponse();
		
		return (response_message);
	} catch (ErrorException &e) {
		client_req = m_client_req_parser.makeClientRequest();

		if (client_req.getHeader().find("host") == client_req.getHeader().end())
			server = m_config.getServer(ip, port);
		else
			server = m_config.getServer(ip, port, *client_req.getHeader().at("host").begin());

		longest_location = findLongestLocation(server, client_req.getPath());
		Context	context  = server.getContext(longest_location);

		handleErrorPageDirective(context, e.getCode(), *context.getDirective("root").begin());
	}
	return std::vector<char>();
}
