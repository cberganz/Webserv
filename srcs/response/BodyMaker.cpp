/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/15 20:43:31 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyMaker.hpp"

BodyMaker::BodyMaker()
{
	m_method_fcts["GET"]	= &BodyMaker::getMethod;
	m_method_fcts["POST"]	= &BodyMaker::postMethod;
	m_method_fcts["DELETE"]	= &BodyMaker::deleteMethod;
}

BodyMaker::BodyMaker(const Config &config)
	: m_config(config)
{
	m_method_fcts["GET"]	= &BodyMaker::getMethod;
	m_method_fcts["POST"]	= &BodyMaker::postMethod;
	m_method_fcts["DELETE"]	= &BodyMaker::deleteMethod;

}

BodyMaker::BodyMaker(const BodyMaker &src)
{ *this = src; }

BodyMaker::~BodyMaker()
{}

BodyMaker &BodyMaker::operator=(const BodyMaker &rhs)
{
	if (this != &rhs)
	{
		this->m_body = rhs.m_body;
		this->m_config = rhs.m_config;
	}
	return *this;
}

/** METHOD **/

bool isDirectory(const std::string &path)
{
	struct stat s;

	if (lstat(path.c_str(), &s) == 0)
		if (S_ISDIR(s.st_mode))
			return true;
	return false;
}

const std::string	&BodyMaker::getMethod(const Context& context, std::string path, const ClientRequest& client_req) {
	if (path.back() == '/' and *context.getDirective("autoindex").begin() == "on")
	{
		path += *context.getDirective("index").begin();
		if (access(path.c_str(), F_OK) == -1)
		{
			path = path.substr(0, path.find_last_of("/"));
			return autoIndex(path);
		}
	}
	if (access(path.c_str(), F_OK) == -1 || isDirectory(path))// voir si Nginx gere pareil
		throw ErrorException(404);
	if (*context.getDirective("cgi").begin() == "on" and requiresCGI(path))
		executeCGI(path);
	else
		readFile(path);
	return (m_body);
}

void	BodyMaker::createFile(std::string filename, std::string content, std::string path) {
	filename = path + filename;
	std::ofstream	out(filename.c_str(), std::ios::out | std::ios::app);

	out.clear();
	for (size_t i = 0; i < content.length(); i++)
		out.put(content[i]);
}

void	BodyMaker::post_multipart_form(const ClientRequest& client_req, const Context& context, std::string path) {
	std::string	boundary = client_req.getHeader().at("Content-Type")[0].substr(30);
	std::string body = client_req.getBody();
	int			i = 0;

	while ((i = body.find(boundary, i)) != std::string::npos) {
		i += boundary.length() + 1;
		if (body.find("filename=", i) == std::string::npos)
			break ;
		if (body.find("filename=", i) > body.find(boundary, i)
			|| body[body.find("filename=", i) + 10] == '\"')
			continue ;
		i = body.find("filename=", i) + 10;
		createFile(body.substr(i, body.find("\"", i) - i), 
				body.substr(body.find("\r\n\r\n", i) + 4, body.find("\r\n--" + boundary, i) - body.find("\r\n\r\n", i) - 4),
				path);
	}
}

const std::string	&BodyMaker::postMethod(const Context& context, std::string path, const ClientRequest& client_req) {
	if (client_req.getHeader().find("Content-Type")// voir quoi fare si pas de content-type
		== client_req.getHeader().end())
			return (m_body);// voir quel retour utiliser
	else if (client_req.getHeader().at("Content-Type")[0] == "application/x-www-form-urlencoded")
		return (m_body);// voir quel retour utiliser

	else if (!client_req.getHeader().at("Content-Type")[0].compare(0, 30,"multipart/form-data; boundary="))
		return (post_multipart_form(client_req, context, path), m_body);// voir quel retour utiliser
	return (m_body);// voir quel retour utiliser
}

const std::string	&BodyMaker::deleteMethod(const Context& context, std::string path, const ClientRequest& client_req) {
	(void) context;
	if (access(path.c_str(), F_OK) == -1)
		throw (ErrorException(404));
	if (path.back() == '/' || access(path.c_str(), W_OK) == -1)
		throw (ErrorException(403));
	if (std::remove(path.c_str())) 
		throw (ErrorException(500));
	return (m_body);// voir quel retour utiliser
}

const std::string &BodyMaker::createBody(const Response& response)
{
	m_body.clear();
	MethodFunctions fp = m_method_fcts[response.getClientRequest().getMethod()];
	return (this->*fp)(response.getContext(), response.getPath(), response.getClientRequest());
}

bool BodyMaker::requiresCGI(const std::string &path)
{
	std::string extension = path.substr(path.find_last_of(".") + 1);
	for (int i = 0 ; i < MAX_EXT ; i++)
		if (extensionsTable[i].extension == extension)
			return extensionsTable[i].isCGI;
	throw ErrorException(501);
}

const std::string &BodyMaker::getProgName(const std::string &path)
{
	std::string extension = path.substr(path.find_last_of(".") + 1);
	for (int i = 0 ; i < MAX_EXT ; i++)
		if (extensionsTable[i].extension == extension)
			return extensionsTable[i].progName;
	throw ErrorException(501);
}

void BodyMaker::readFile(const std::string &path)
{
	if (access(path.c_str(), R_OK) == -1)
		throw ErrorException(403);
	std::ifstream file(path);
	if (not file.good())
		throw ErrorException(503);
	m_body = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

//char* BodyMaker::generateEnvp(const ClientRequest &client_req, const Response &response, const std::string &path)
//{
//	std::map<std::string, std::string> envp;
//	// SERVER VARIABLES
//	envp["SERVER_SOFTWARE"] = "WEBSERV/42.0";
//	envp["SERVER_NAME"] = response.getContext().getDirective("ip");
//	envp["GATEWAY_INTERFACE"] = "CGI/1.1";
//	// REQUEST DEFINED VARIABLES
//	envp["SERVER_PROTOCOL"] = "HTTP/1.1";
//	envp["SERVER_PORT"] = response.getContext().getDirective("port");
//	envp["REQUEST_METHOD"] = client_req.getMethod();
//	// envp["PATH_INFO"]
//	// envp["PATH_TRANSLATED"]
//	envp["SCRIPT_NAME"] = path;
//	envp["QUERY_STRING"] = client_req.getQuery();
//	if (client_req.getHeader().find("host") != client_req.getHeader().end())
//		envp["REMOTE_HOST"] = client_req.getHeader()["host"]; 
//	else
//		envp["REMOTE_HOST"] = "";
//	// envp["REMOTE_ADDR"] -> IP DU CLIENT necessary ?
//	// envp["AUTH_TYPE"]
//	// envp["REMOTE_USER"]
//	envp["CONTENT_TYPE"] = client_req.getHeader()["content-type"];
//	envp["CONTENT_LENGTH"] = client_req.getBody().size();
//	// CLIENT VARIABLES
//	envp[""] = client_req.getHeader()[""];
//}

void BodyMaker::executeCGI(std::string &path)
{
	int pid, stat, fd[2];

	if (access(path.c_str(), X_OK) == -1)
		throw ErrorException(403);
	if (pipe(fd) != 0)
		throw ErrorException(503);
	pid = fork();
	if (pid == -1)
		throw ErrorException(500);
	else if (pid == 0) // child process
	{
		close(fd[0]);
		close(STDOUT_FILENO);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fd[1]);
		char* binPath = strdup(getProgName(path).c_str());
		char* progPath = strdup(path.c_str());
		char* argv[3] = { binPath, progPath, NULL };
		execve(binPath, argv, NULL);
		free(binPath);
		free(progPath);
		exit(1);
	}
	else // parent process
	{
		waitpid(pid, &stat, 0);
		stat = WEXITSTATUS(stat);
		if (stat != 0)
			throw ErrorException(500);
		close(fd[1]);
		int	 ret = 0;
		char buff[1024];
		memset(buff, 0, 1024);
		while ((ret = read(fd[0], buff, 1024)) > 0)
			m_body += buff;
		if (ret < 0)
			throw ErrorException(500);
		close(fd[0]);
	}
}

const std::string &BodyMaker::autoIndex(std::string &path)
{
	DIR*			dir;
	struct dirent*	dirent;
	char			buff[1024];

	path.insert(0, getcwd(buff, 1024) + std::string("/"));
	dir = opendir(path.c_str());
	if (dir == NULL)
		throw ErrorException(404);
	m_body += "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"utf-8\" />\n\t\t<title>\n\t\t\tAUTOINDEX\n\t\t</title>\n\t</head>\n\n\t<body>\n\t\t<h2>\n\t\t\tWEBSERV AUTOINDEX: ";
	m_body += path;
	m_body += "\n\t\t</h2>\n";
    while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_type == DT_DIR)
			m_body += "\t\t<h4 style=\"color:blue;\"><a href=\"";
		else
			m_body += "\t\t<h4 style=\"color:black;\"><a href=\"";
		m_body += dirent->d_name;
		if (dirent->d_type == DT_DIR)
			m_body += "/";
		m_body += "\">\n\t\t\t";
		m_body += dirent->d_name;
		m_body += "\n\t\t</a></h4>\n";
	}
	closedir(dir);
	m_body += "\t</body>\n</html>";
	return m_body;
}
