#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include <sstream>
# include <utility>
# include "../tools/ErrorException.hpp"

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
		void						replace_encode_char(std::string &str);
		void						trimNewLine(std::string &str);
		void						parse_request_line(std::string str);
		bool						is_request_line_correct();
		bool						is_method_correct();
		bool						is_path_correct();
		bool						is_http_version_correct();
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
		ClientRequest	&operator=(const ClientRequest &copy);
		std::string											getPath() const;
		std::string											getMethod() const;
		std::string											getHttpVersion() const;
		std::string											getBody() const;
		std::map<std::string, std::vector<std::string> >	getHeader() const;

};

#endif