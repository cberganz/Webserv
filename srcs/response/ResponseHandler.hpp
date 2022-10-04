#ifndef RESPONSEHANDLER_HPP
# define RESPONSEHANDLER_HPP

# include "Response.hpp"
# include "../client_request/ClientRequest.hpp"

class ResponseHandler {
	protected:
		ClientRequest	m_client_request;
		ClientRequest	m_client_request;


	private:


	public:
		ResponseHandler();
		ResponseHandler(const std::string client_request);
		ResponseHandler(const ResponseHandler &copy);
		~ResponseHandler();
		ResponseHandler	&operator=(const ResponseHandler &copy);
};

#endif