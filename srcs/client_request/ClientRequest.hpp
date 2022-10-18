#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP

# include <map>
# include <vector>
# include <string>
# include <iostream>
# include <utility>
# include "../tools/ErrorException.hpp"

class ClientRequest {
	protected:
		std::string											m_method;
		std::string											m_path;
		std::string											m_http_version;
		std::vector<char>									m_body;
		std::map<std::string, std::vector<std::string> > 	m_header;
		std::string											m_query;


	public:
		ClientRequest();
		ClientRequest(const ClientRequest &copy);
		~ClientRequest();

		ClientRequest
		&operator=(const ClientRequest &copy);

		void	print();

		/*
		**	GETTER
		*/
		const std::string
		getPath() const;

		const std::string
		getMethod() const;

		const std::string
		getHttpVersion() const;

		const std::vector<char>
		getBody() const;

		const std::map<std::string, std::vector<std::string> >
		getHeader() const;

		const std::string
		getQuery() const;

		/*
		**	SETTER
		*/
		void
		setPath(std::string path);

		void
		setMethod(std::string method);

		void
		setHttpVersion(std::string http_version);

		void
		setBody(std::vector<char> body);

		void
		setHeader(std::map<std::string, std::vector<std::string> > header);

		void
		setQuery(std::string qery);
};

#endif