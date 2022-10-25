#ifndef CLIENTREQUESTPARSER_HPP
# define CLIENTREQUESTPARSER_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>
# include <utility>
# include <algorithm>
# include "ClientRequest.hpp"
# include "../tools/ErrorException.hpp"
# include "../tools/utility.hpp"

class ClientRequestParser {
	protected:
		std::vector<char>	m_request;

	public:
		ClientRequestParser();
		ClientRequestParser(const std::vector<char> client_request);
		ClientRequestParser(const ClientRequestParser &copy);
		~ClientRequestParser();
		ClientRequestParser	&operator=(const ClientRequestParser &copy);

		void
		setRequest(const std::vector<char> request);

		ClientRequest
		makeClientRequest();

	private:
		std::vector<std::string>
		tokenise(std::string str, char sep);

		std::string
		strToLower(std::string str);

		void
		trimBegin(std::string &str, std::string charset);

		void
		trimEnd(std::string &str, std::string charset);

		void
		replace_encode_char(std::string &str);
		
		bool
		is_request_line_correct(ClientRequest client_requ);

		bool
		is_path_correct(std::string path);

		bool
		is_http_version_correct(std::string http_version);
		
		void
		parse_request_line(std::string str, ClientRequest &client_req);

		std::map<std::string, std::vector<std::string> >
		parse_header(std::string str);

		std::vector<char>
		parse_body(std::vector<char> str);

		std::string
		getStringHeader();
};

#endif
