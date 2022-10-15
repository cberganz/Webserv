/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdine <cdine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/15 17:48:30 by cdine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyMaker.hpp"

BodyMaker::BodyMaker()
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
		this->m_body = rhs.m_body;
	return *this;
}

/** METHOD **/
const std::string	&BodyMaker::CallMethod( const std::string & s,
											const Context& context,
											std::string path,
											const ClientRequest& client_req) {
	MethodFunctions fp = m_method_fcts[s];
	return (this->*fp)(context, path, client_req);
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
	else
		path += "/" + *context.getDirective("index").begin();
	if (access(path.c_str(), F_OK) == -1)
		throw ErrorException(404);
	if (requiresCGI(path))
		executeCGI(path);
	else
		readFile(path);
	return (m_body);
}

void	BodyMaker::createFile(std::string filename, std::string content, std::string path) {
	filename = path + filename;
	std::ofstream	out(filename.c_str(), std::ios::out | std::ios::binary);
	size_t			size = content.size();

	out.clear();
	out.write(content.c_str(), size);
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

const std::string &BodyMaker::createBody(const Context& context, const ClientRequest& client_req)
{
	m_body.clear();
	std::string path;
	if (context.directiveExist("root"))
		path = *context.getDirective("root").begin();
	path += client_req.getPath();
	return (CallMethod(client_req.getMethod(), context, path, client_req));
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

void BodyMaker::executeCGI(std::string &path)
{
	int pid, stat, fd[2];

	if (access(path.c_str(), X_OK) == -1)
		throw ErrorException(403);
	if (pipe(fd) != 0)
		throw ErrorException(503);
	pid = fork();
	if (pid == 0) // child process
	{
		close(fd[0]);
		close(STDOUT_FILENO);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fd[1]);
		char* binPath = strdup(getProgName(path).c_str()); // generate bin path ??
		char* progPath = strdup(path.c_str());
		char* argv[3] = { binPath, progPath, NULL };
		execve(binPath, argv, NULL);
		free(binPath);
		free(progPath);
		exit(1);
	}
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
