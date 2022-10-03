/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderMaker.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 03:26:44 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 04:17:03 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERMAKER_HPP
# define HEADERMAKER_HPP

# include <string>
# include "../tools/utility.hpp"
# include "HttpCodes.hpp"
# include "headersTable.hpp"

# define NEWLINE "\r\n"
# define MAX_FIELDS 12

class HeaderMaker {

public:
	typedef bool (HeaderMaker::*conditions)();
	typedef void (HeaderMaker::*fields)();

	HeaderMaker();
	HeaderMaker(const HeaderMaker &src);
	~HeaderMaker();

	HeaderMaker &operator=(const HeaderMaker &rhs);

	std::string createHeader();

private:
	HttpCodes			m_httpCodes;
	std::string			m_header;
	static fields		m_fields[];
	static conditions	m_conditions[];

	bool condition_date();
	bool condition_server();
	bool condition_location();
	bool condition_connection();
	bool condition_retry_after();
	bool condition_last_modified();
	bool condition_www_authenticate();
	bool condition_transfert_encoding();
	bool condition_content_type();
	bool condition_content_lenght();
	bool condition_content_location();
	bool condition_content_language();

	void head();
	void date();
	void server();
	void location();
	void connection();
	void retry_after();
	void last_modified();
	void www_authenticate();
	void transfert_encoding();
	void content_type();
	void content_lenght();
	void content_location();
	void content_language();

}; // class HeaderMaker

#endif // HEADERMAKER_HPP
