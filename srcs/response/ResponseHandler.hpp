#ifndef RESPONSEHANDLER_HPP
# define RESPONSEHANDLER_HPP

#include <algorithm>
# include "ResponseMaker.hpp"
# include "../client_request/ClientRequestParser.hpp"

class ResponseHandler {
	protected:
		ClientRequestParser	m_client_req_parser;
		ResponseMaker		m_response_maker;
		Config				m_config;

	public:
		ResponseHandler();
		ResponseHandler(const Config &config);
		ResponseHandler(const ResponseHandler &copy);
		~ResponseHandler();
		ResponseHandler	&operator=(const ResponseHandler &copy);

		void		setClientRequest(std::vector<char> client_request);

		std::vector<char> createResponseMessage(const std::string &ip, const std::string &port);

};

#endif