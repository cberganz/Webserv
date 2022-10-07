#ifndef RESPONSEHANDLER_HPP
# define RESPONSEHANDLER_HPP

# include "ResponseMaker.hpp"
# include "../client_request/ClientRequestParser.hpp"

class ResponseHandler {
	protected:
		ClientRequestParser	m_client_req_parser;
		ResponseMaker		m_response_maker;

	public:
		ResponseHandler();
		ResponseHandler(const Config &config);
		ResponseHandler(const ResponseHandler &copy);
		~ResponseHandler();
		ResponseHandler	&operator=(const ResponseHandler &copy);

		void		setClientRequest(std::string client_request);

		std::string createResponseMessage(const std::string &ip, const std::string &port);

};

#endif