/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:19:33 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/24 12:39:54 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include "../config_lexer_parser/Config.hpp"
# include "../client_request/ClientRequest.hpp"

class Response {

public:
	Response();
	Response(const ClientRequest &client_req, const Context &context, const std::string &longest_location);
	~Response();
	Response(const Response &src);

	Response &operator=(const Response &rhs);

	const std::vector<char>	&getResponse() const;
	const int 				&getHttpCode() const;
	const std::string		&getPath() const;
	const Context			&getContext() const;
	const ClientRequest		&getClientRequest() const;
	const std::string		&getLocation() const;
	bool					isCGI() const;

	void setHttpCode(const int &code);
	void setPath(const std::string &longest_location);
	void setContext(const Context &context);
	void setClientRequest(const ClientRequest &client_req);
	void setLocation(const std::string &location);
	void setCGI(bool isCGI);

	void append(const std::vector<char> &str);
	void insert(size_t index, const std::string &str);

private:
	int					m_httpCode;
	std::vector<char> 	m_response;
	std::string 		m_path;
	std::string 		m_location;
	Context 			m_context;
	ClientRequest 		m_client_req;
	bool				m_isCGI;

}; // class Response

#endif // RESPONSE_HPP
