/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMaker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:00:19 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 05:41:03 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEMAKER_HPP
# define RESPONSEMAKER_HPP

# include <string>
# include "Response.hpp"
# include "HttpCodes.hpp"
# include "HeaderMaker.hpp"
# include "BodyMaker.hpp"
# include "../config_lexer_parser/Config.hpp"

class ResponseMaker {

public:
	ResponseMaker();
	ResponseMaker(const Config &config);
	~ResponseMaker();
	ResponseMaker(const ResponseMaker &src);

	ResponseMaker& operator=(const ResponseMaker &rhs);

	Response* createResponse(const std::string &uri, const std::string &ip, const std::string &port);

private:
	HttpCodes	m_httpCodes;
	Config		m_config;
	HeaderMaker	m_headerMaker;
	BodyMaker	m_bodyMaker;

}; // class ResponseMaker

#endif // RESPONSEMAKER_HPP
