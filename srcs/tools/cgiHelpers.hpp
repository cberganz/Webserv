/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgiHelpers.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student42.fr>	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:40:04 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/16 21:59:49 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHELPERS_HPP
# define CGIHELPERS_HPP

# include "../config_lexer_parser/Context.hpp"
# include "../client_request/ClientRequest.hpp"

std::string joinStrVector(const std::vector<std::string> &v, std::string delim)
{
    std::stringstream ss;
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<std::string>(ss, delim.c_str()));
    return ss.str();
}

char** mapToEnvp(const std::map<std::string, std::string>& m)
{
	std::vector<std::string> v;
	for (std::map<std::string, std::string>::const_iterator it = m.begin() ; it != m.end() ; it++)
		v.push_back(it->first + "=" + it->second);
	char** arr = (char**)malloc((v.size() + 1) * sizeof(*arr));
	if (arr == NULL)
		exit(501);
	std::vector<std::string>::size_type index = 0;
	for (std::vector<std::string>::iterator it = v.begin() ; it != v.end() ; it++)
	{
		arr[index] = strdup(it->c_str());
		if (arr[index] == NULL)
			exit(501);
		index++;
	}
	arr[index] = NULL;
	return arr;
}

std::string getMime(const std::string& path)
{
	std::string extension = path.substr(path.find_last_of(".") + 1);
	for (int i = 0 ; i < MAX_EXT ; i++)
		if (extensionsTable[i].extension == extension)
			return extensionsTable[i].MIMEType + "; charset=UTF-8";
	return "";
}

char** generateEnvp(const ClientRequest &client_req, const Context &context, const std::string &path)
{
	std::map<std::string, std::string> envp;

	// SERVER VARIABLES
	envp["SERVER_SOFTWARE"] = "WEBSERV/42.0";
	envp["SERVER_NAME"] = *context.getDirective("ip").begin();
	envp["GATEWAY_INTERFACE"] = "CGI/1.1";

	// REQUEST DEFINED VARIABLES
	envp["SERVER_PROTOCOL"] = "HTTP/1.1";
	envp["SERVER_PORT"] = *context.getDirective("port").begin();
	envp["REQUEST_METHOD"] = client_req.getMethod();
	envp["REDIRECT_STATUS"] = ft::itostr(200); // Security variable: php does not accept exec if not set. How to handle it ?
	envp["PATH_INFO"] = path; //to parse in clientRequest?
	envp["PATH_TRANSLATED"] = path;
	envp["SCRIPT_NAME"] = path; // script_name or script_filename ?
	envp["SCRIPT_FILENAME"] = path; // script_name or script_filename ?
	envp["QUERY_STRING"] = client_req.getQuery();
	// if (client_req.getHeader().count("host"))
	envp["REMOTE_HOST"] = ""/* joinStrVector(client_req.getHeader().find("host")->second, ",") */;
	envp["REMOTE_ADDR"] = "";/* -> IP DU CLIENT necessary ? */
	envp["AUTH_TYPE"] = "";
	envp["REMOTE_USER"] = "";


	if (client_req.getHeader().count("content-type"))
		envp["CONTENT_TYPE"] = client_req.getHeader().find("content-type")->second[0];
	else
		envp["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	envp["CONTENT_LENGTH"] = ft::itostr(client_req.getBody().size());

	// std::cout << "\nBODY SIZE: " << ft::itostr(client_req.getBody().size()) << "\n";
	// CLIENT VARIABLES
	// if (client_req.getHeader().count("accept"))
	envp["HTTP_ACCEPT"] = "*/*";//joinStrVector(client_req.getHeader().find("accept")->second, ",");
	// if (client_req.getHeader().count("accept-language"))
	envp["HTTP_ACCEPT_LANGUAGE"] = "en-US,en";//joinStrVector(client_req.getHeader().find("accept-language")->second, ",");
	if (client_req.getHeader().count("user-agent"))
		envp["HTTP_USER_AGENT"] = joinStrVector(client_req.getHeader().find("user-agent")->second, ",");
	if (client_req.getHeader().count("cookie"))
		envp["HTTP_COOKIE"] = joinStrVector(client_req.getHeader().find("cookie")->second, ",");
	envp["HTTP_REFERER"] = "";
	
	// for (std::map<std::string, std::string>::iterator it = envp.begin() ; it != envp.end() ; it++)
	// 	std::cout << it->first << " -> " << it->second << std::endl;

	return mapToEnvp(envp);
}

#endif // CGIHELPERS_HPP