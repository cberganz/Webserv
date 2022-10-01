/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpCodes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:03:21 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/01 20:27:05 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPCODES_HPP
# define HTTPCODES_HPP

# include <string>

# define MAX_CODE 599

class HttpCodes {

public:
	HttpCodes();
	HttpCodes(const HttpCodes &src);
	~HttpCodes();

	HttpCodes &operator=(const HttpCodes &rhs);
	const std::string &operator[](int code) const;

private:
	std::string m_codes[MAX_CODE + 1];

	class InvalidCodeException : public std::exception
    {
	private:
		const std::string message;

    public:
		InvalidCodeException();
		~InvalidCodeException() throw();

        const char* what() const throw();
    };

}; // class HttpCodes

#endif // HTTPCODES_HPP
