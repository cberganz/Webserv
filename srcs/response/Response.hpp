/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:19:33 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/13 20:26:46 by rbicanic         ###   ########.fr       */
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

	const std::string	&getResponse() const;
	const int 			&getHttpCode() const;
	const std::string	&getPath() const;
	const Context		&getContext() const;
	const ClientRequest	&getClientRequest() const;
	const std::string	&getLocation() const;

	void setHttpCode(const int &code);
	void setPath(const std::string &longest_location);
	void setContext(const Context &context);
	void setClientRequest(const ClientRequest &client_req);
	void setLocation(const std::string &location);

	void append(const std::string &str);
	void insert(std::string::size_type index, const std::string &str);

private:
	int				m_httpCode;
	std::string 	m_response;
	std::string 	m_path;
	std::string 	m_location;
	Context 		m_context;
	ClientRequest 	m_client_req;

}; // class Response

#endif // RESPONSE_HPP
