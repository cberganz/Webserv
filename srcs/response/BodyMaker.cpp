/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/19 16:03:56 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyMaker.hpp"
#include "../tools/cgiHelpers.hpp"

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

const std::string	&BodyMaker::getMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req) {
	if (path.back() == '/' and *context.getDirective("autoindex").begin() == "on")
	{
		path += *context.getDirective("index").begin();
		if (access(path.c_str(), F_OK) == -1)
		{
			path = path.substr(0, path.find_last_of("/"));
			return autoIndex(path);
		}
	}
	if (access(path.c_str(), F_OK) == -1 or isDirectory(path))// voir si Nginx gere pareil
		throw ErrorException(404);
	if (*context.getDirective("cgi").begin() == "on" and requiresCGI(path))
	{
		executeCGI(client_req, path, generateEnvp(client_req, context, path));
		response.setCGI(true);
	}
	else
		readFile(path);
	return (m_body);
}

void	BodyMaker::createFile(std::string filename, std::vector<char> content, std::string path) {
	if (*path.end() != '/') {
		int	i = path.length();
		while (i > 0 && path[i] != '/')
			i--;
		path = path.substr(0, i + 1);
	}
	filename = path + filename;
	std::ofstream	out(filename.c_str(), std::ios::out | std::ios::app);
	out.clear();
	for (std::vector<char>::iterator it = content.begin(); it != content.end(); it++)
		out.put(*it);
}

void	BodyMaker::post_multipart_form(const ClientRequest& client_req, const Context& context, std::string path) {
	std::string			boundary = client_req.getHeader().at("content-type")[0].substr(30);
	std::vector<char>	body = client_req.getBody();
	int					i = 0;

	while ((i = ft::search_vector_char(body, boundary.c_str(), i)) != -1) {
		i += boundary.length() + 1;
		if (ft::search_vector_char(body, "filename=", i) == -1)
			break ;
		if (ft::search_vector_char(body, "filename=", i) > ft::search_vector_char(body, boundary.c_str(), i)
			|| body[ft::search_vector_char(body, "filename=", i) + 10] == '\"')
			continue ;
		i = ft::search_vector_char(body, "filename=", i) + 10;

		std::string			filename(body.begin() + i, body.begin() + ft::search_vector_char(body, "\"", i));
		std::vector<char>	content(body.begin() + ft::search_vector_char(body, "\r\n\r\n", i) + 4,
									body.begin() + ft::search_vector_char(body, "\r\n\r\n", i) + 4 + 
									ft::search_vector_char(body, ("\r\n--" + boundary).c_str(), i) - ft::search_vector_char(body, "\r\n\r\n", i) - 4);
		createFile(filename, content, path);
	}
}

const std::string	&BodyMaker::postMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req) {
	
	if (*context.getDirective("cgi").begin() == "on" and requiresCGI(path))
	{
		executeCGI(client_req, path, generateEnvp(client_req, context, path));
		response.setCGI(true);
		return (m_body);
	}
	if (client_req.getHeader().find("content-type")// voir quoi fare si pas de content-type
		== client_req.getHeader().end())
			return (m_body);// voir quel retour utiliser
	else if (client_req.getHeader().at("content-type")[0] == "application/x-www-form-urlencoded")
		return (m_body);// voir quel retour utiliser

	else if (!client_req.getHeader().at("content-type")[0].compare(0, 30,"multipart/form-data; boundary="))
		return (post_multipart_form(client_req, context, path), m_body);// voir quel retour utiliser
	return (m_body);// voir quel retour utiliser
}

const std::string	&BodyMaker::deleteMethod(Response& response, const Context& context, std::string path, const ClientRequest& client_req) {
	(void) context;
	if (access(path.c_str(), F_OK) == -1)
		throw (ErrorException(404));
	if (path.back() == '/' || access(path.c_str(), W_OK) == -1)
		throw (ErrorException(403));
	if (std::remove(path.c_str())) 
		throw (ErrorException(500));
	return (m_body);// voir quel retour utiliser
}

const std::string &BodyMaker::createBody(Response& response)
{
	m_body.clear();
	MethodFunctions fp = m_method_fcts[response.getClientRequest().getMethod()];
	return (this->*fp)(response, response.getContext(), response.getPath(), response.getClientRequest());
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

void BodyMaker::executeCGI(const ClientRequest& client_req, const std::string &path, char **envp)
{
	int pid, stat, fd[2];

	if (access(path.c_str(), X_OK) == -1)
		throw ErrorException(403);
	if (pipe(fd) != 0)
		throw ErrorException(503);
	pid = fork();
	if (pid == -1)
		throw ErrorException(500);
	if (pid == 0) // child process
	{
		close(fd[0]);
		close(STDOUT_FILENO);
	
		std::vector<char> copy(client_req.getBody());
		copy.push_back('\0');
		std::FILE* tmpf = std::tmpfile();
		std::fputs(&copy[0], tmpf);
		 char buf[49];
		std::fgets(buf, sizeof(buf), tmpf);
		std::cout << buf << '\n';
		if (dup2(fileno(tmpf), STDIN_FILENO) == -1)
			exit(1);


		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fd[1]);
		char* binPath = strdup(getProgName(path).c_str());
		char* progPath = strdup(path.c_str());
		char* argv[3] = { binPath, progPath, NULL };
		execve(binPath, argv, envp);
		for (int i = 0 ; envp[i] != NULL ; i++)
			free(envp[i]);
		free(envp);
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
		char buff[4096];
		memset(buff, 0, 4096);
		while ((ret = read(fd[0], buff, 4096)) > 0)
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
