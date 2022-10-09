/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMaker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:00:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/09 21:50:56 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEMAKER_HPP
# define RESPONSEMAKER_HPP

# include <string>
# include <algorithm>
# include <cctype>
# include "Response.hpp"
# include "HttpCodes.hpp"
# include "HeaderMaker.hpp"
# include "BodyMaker.hpp"
# include "../config_lexer_parser/Config.hpp"
# include "../client_request/ClientRequest.hpp"

class ResponseMaker {

public:
	ResponseMaker();
	ResponseMaker(const Config &config);
	~ResponseMaker();
	ResponseMaker(const ResponseMaker &src);

	ResponseMaker& operator=(const ResponseMaker &rhs);

	bool		isMethodAllowed(Context &context, ClientRequest &client_req);
	bool		isBodySizeLimitReached(Context &context, ClientRequest &client_req);
	void		handleErrorPageDirective(Context &context, int error_status);

	Response*	createResponse(ClientRequest &client_req, const std::string &ip, const std::string &port);

private:
	HttpCodes	m_httpCodes;
	Config		m_config;
	HeaderMaker	m_headerMaker;
	BodyMaker	m_bodyMaker;

}; // class ResponseMaker

#endif // RESPONSEMAKER_HPP
