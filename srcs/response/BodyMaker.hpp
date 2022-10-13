/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/12 19:21:06 by rbicanic         ###   ########.fr       */
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
# include <cstdio>
# include <filesystem>
# include "../tools/ErrorException.hpp"
# include "../config_lexer_parser/Context.hpp"
# include "../client_request/ClientRequest.hpp"
# include "../tools/utility.hpp"
# include "extensionsTable.hpp"
# include "Response.hpp"

# define UPLOAD_PATH "./upload"

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(const Response &response);

private:
	typedef const std::string& (BodyMaker::*MethodFunctions)(const Context&, std::string path, const ClientRequest&);

	std::map<std::string, MethodFunctions>	m_method_fcts;
	std::string 							m_body;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(std::string &path);
	const std::string &autoIndex(std::string &path);

	/** METHODS **/
	const std::string	&getMethod(const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&postMethod(const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&deleteMethod(const Context& context, std::string path, const ClientRequest& client_req);
	void				post_multipart_form(const ClientRequest& client_req, const Context& context, std::string path);
	void				createFile(std::string filename, std::string content, std::string path);

	// void	post_urlencoded()

};

#endif // BODYMAKER_HPP
