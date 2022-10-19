/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/19 12:57:42 by cdine            ###   ########.fr       */
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
# include "../config_lexer_parser/Config.hpp"
# include "../client_request/ClientRequest.hpp"
# include "../tools/utility.hpp"
# include "extensionsTable.hpp"
# include "Response.hpp"

# define UPLOAD_PATH "./upload"

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const Config &config);
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(Response &response);

private:
	typedef const std::string& (BodyMaker::*MethodFunctions)(Response& response, const Context&, std::string path, const ClientRequest&);

	std::map<std::string, MethodFunctions>	m_method_fcts;
	std::string 							m_body;
	Config									m_config;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(const std::string &path, char **envp);
	const std::string &autoIndex(std::string &path);

	/** METHODS **/
	const std::string	&getMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&postMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&deleteMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	void				post_multipart_form(const ClientRequest& client_req, const Context& context, std::string path);
	void				createFile(std::string filename, std::vector<char> content, std::string path);
	bool				check_end_boundary(std::string boundary, std::vector<char> &body);

	// void	post_urlencoded()

};

#endif // BODYMAKER_HPP
