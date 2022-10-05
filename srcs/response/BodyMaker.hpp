/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/05 02:28:17 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODYMAKER_HPP
# define BODYMAKER_HPP

# include <string>
# include <fstream>
# include <cstring>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../tools/ErrorException.hpp"
# include "../config_lexer_parser/Context.hpp"
# include "extensionsTable.hpp"

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(const Context &context, const std::string &uri);

private:
	std::string m_body;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(std::string &path);
	const std::string &autoIndex(std::string &path);

};

#endif // BODYMAKER_HPP
