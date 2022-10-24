/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/24 19:03:26 by rbicanic         ###   ########.fr       */
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
# include <sys/stat.h>
# include "../tools/ErrorException.hpp"
# include "../config_lexer_parser/Context.hpp"
# include "../config_lexer_parser/Config.hpp"
# include "../client_request/ClientRequest.hpp"
# include "../tools/utility.hpp"
# include "extensionsTable.hpp"
# include "Response.hpp"

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const Config &config);
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::vector<char> &createBody(Response &response);

private:
	typedef const std::vector<char>& (BodyMaker::*MethodFunctions)(Response& response, const Context&, std::string path, const ClientRequest&);

	std::map<std::string, MethodFunctions>	m_method_fcts;
	std::vector<char>						m_body;
	Config									m_config;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(const ClientRequest& client_req, const std::string &path, char **envp);
	const std::vector<char> &autoIndex(std::string &path);

	/** METHODS **/
	const std::vector<char>	&getMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	const std::vector<char>	&postMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	const std::vector<char>	&deleteMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req);
	void					post_multipart_form(Response& response, const ClientRequest& client_req, std::string path);
	void					createFile(std::string filename, std::vector<char> content, std::string path);
	bool					check_end_boundary(std::string boundary, std::vector<char> &body);
	std::string				getUploadFolder(const Context& context, std::string path);
};

#endif // BODYMAKER_HPP
