/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/02 19:11:41 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODYMAKER_HPP
# define BODYMAKER_HPP

# include <string>
# include <fstream>

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(const std::string &path);

private:
	std::string m_body;

};

#endif // BODYMAKER_HPP
