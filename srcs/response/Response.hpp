/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:19:33 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 05:22:50 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>

class Response {

public:
	Response();
	~Response();
	Response(const Response &src);

	Response &operator=(const Response &rhs);

	const std::string &getResponse();

	void append(const std::string &str);
	void setHttpCode(const int &code);

private:
	std::string m_response;
	int			m_httpCode;

}; // class Response

#endif // RESPONSE_HPP
