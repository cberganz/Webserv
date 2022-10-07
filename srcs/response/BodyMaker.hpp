/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/07 18:21:08 by cdine            ###   ########.fr       */
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
# include <cstdio>

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(const Context &context, const std::string &uri, const std::string &method);

private:
	std::string m_body;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(std::string &path);
	const std::string &autoIndex(std::string &path);

	/** METHODS **/
	const std::string	&getMethod(const Context& context, std::string path);
	void				postMethod(std::string path);
	void				deleteMethod(std::string path);

};

#endif // BODYMAKER_HPP
