/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderMaker.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:26:44 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/13 20:23:48 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERMAKER_HPP
# define HEADERMAKER_HPP

# include <string>
# include "../tools/utility.hpp"
# include "HttpCodes.hpp"
# include "headersTable.hpp"
# include "extensionsTable.hpp"
# include "../client_request/ClientRequest.hpp"
# include "Response.hpp"

# define NEWLINE "\r\n"
# define MAX_FIELDS 12

class HeaderMaker {

public:
	typedef bool (HeaderMaker::*conditions)(const ClientRequest &client_req, const Response &response);
	typedef void (HeaderMaker::*fields)(const ClientRequest &client_req, const Response &response);

	HeaderMaker();
	HeaderMaker(const HeaderMaker &src);
	~HeaderMaker();

	HeaderMaker &operator=(const HeaderMaker &rhs);

	std::string createHeader(const ClientRequest &client_req, const Response &response);

private:
	HttpCodes			m_httpCodes;
	std::string			m_header;
	static fields		m_fields[];
	static conditions	m_conditions[];

	bool condition_date(const ClientRequest &client_req, const Response &response);
	bool condition_server(const ClientRequest &client_req, const Response &response);
	bool condition_location(const ClientRequest &client_req, const Response &response);
	bool condition_connection(const ClientRequest &client_req, const Response &response);
	bool condition_retry_after(const ClientRequest &client_req, const Response &response);
	bool condition_last_modified(const ClientRequest &client_req, const Response &response);
	bool condition_www_authenticate(const ClientRequest &client_req, const Response &response);
	bool condition_transfert_encoding(const ClientRequest &client_req, const Response &response);
	bool condition_content_type(const ClientRequest &client_req, const Response &response);
	bool condition_content_lenght(const ClientRequest &client_req, const Response &response);
	bool condition_content_location(const ClientRequest &client_req, const Response &response);
	bool condition_content_language(const ClientRequest &client_req, const Response &response);

	void head(const Response &response);
	void date(const ClientRequest &client_req, const Response &response);
	void server(const ClientRequest &client_req, const Response &response);
	void location(const ClientRequest &client_req, const Response &response);
	void connection(const ClientRequest &client_req, const Response &response);
	void retry_after(const ClientRequest &client_req, const Response &response);
	void last_modified(const ClientRequest &client_req, const Response &response);
	void www_authenticate(const ClientRequest &client_req, const Response &response);
	void transfert_encoding(const ClientRequest &client_req, const Response &response);
	void content_type(const ClientRequest &client_req, const Response &response);
	void content_lenght(const ClientRequest &client_req, const Response &response);
	void content_location(const ClientRequest &client_req, const Response &response);
	void content_language(const ClientRequest &client_req, const Response &response);

}; // class HeaderMaker

#endif // HEADERMAKER_HPP
