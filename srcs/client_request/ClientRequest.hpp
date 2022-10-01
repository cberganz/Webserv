#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include <sstream>
# include <utility>

typedef struct sockaddr_in  t_sockaddr_in;// voir la bonne position

class ClientRequest {
	protected:
		std::string											m_method;
		std::string											m_path;
		std::string											m_http_version;
		std::string											m_body;
		std::map<std::string, std::vector<std::string> > 	m_header;


	private:
		std::vector<std::string>	tokenise(std::string str, char sep);
		void						parse_request_line(std::string str);
		void						print();


		class ClientRequestException : public std::exception {
			private:
				std::string m_msg;

			public:
				ClientRequestException(std::string msg);
				~ClientRequestException() throw();
				const char *what() const throw();
		};

	public:
		ClientRequest();
		ClientRequest(const std::string client_request);
		ClientRequest(const ClientRequest &copy);
		~ClientRequest();
		ClientRequest  &operator=(const ClientRequest &copy);
};

#endif