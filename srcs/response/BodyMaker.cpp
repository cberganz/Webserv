/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/26 13:55:13 by rbicanic         ###   ########.fr       */
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

const std::vector<char>	&BodyMaker::getMethod(Response& 			response,
											  const Context& 		context,
											  std::string 			path,
											  const ClientRequest&	client_req)
{
	if (path[path.size() - 1] == '/' and *context.getDirective("autoindex").begin() == "on")
	{
		path += *context.getDirective("index").begin();
		if (access(path.c_str(), F_OK) == -1)
		{
			path = path.substr(0, path.find_last_of("/"));
			return autoIndex(path);
		}
	}
	if (access(path.c_str(), F_OK) == -1 or isDirectory(path))
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

void	BodyMaker::createFile(std::string filename, std::vector<char> content, std::string path)
{
	filename = path + filename;
	std::ofstream	out(filename.c_str(), std::ios::out | std::ios::app);
	out.clear();
	for (std::vector<char>::iterator it = content.begin(); it != content.end(); it++)
		out.put(*it);
}

bool 	BodyMaker::check_end_boundary(std::string boundary, std::vector<char> &body) {
	boundary = "--" + boundary + "--";
	if (ft::search_vector_char(body, boundary.c_str(), body.size() - boundary.length() - 10) == -1)
		return (false);
	return (true);
}


void	BodyMaker::post_multipart_form(Response& response,
									   const ClientRequest& client_req,
									   std::string path)
{
	std::string			boundary = client_req.getHeader().at("content-type")[0].substr(30);
	std::vector<char>	body = client_req.getBody();
	int					i = 0;

	if (!check_end_boundary(boundary, body))
		throw ErrorException(400);
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
		response.setHttpCode(201);
	}
}

std::string	BodyMaker::getUploadFolder(const Context& context, std::string path) {
	if (path[path.size() - 1] != '/') {
		int	i = path.length() - 1;
		while (i > 0 && path[i] != '/')
			i--;
		path = path.substr(0, i + 1);
	}
	if (*context.getDirective("upload_folder").begin() != ".") {
		path = *context.getDirective("upload_folder").begin();
		if (path[path.size() - 1] != '/')
			path += "/";
		if (access(path.c_str(), F_OK) == -1 || access(path.c_str(), W_OK) == -1)
			throw (ErrorException(404));
	}
	return (path);
}

const std::vector<char>	&BodyMaker::postMethod(Response& response,
											   const Context& context,
											   std::string path,
											   const ClientRequest& client_req)
{
	std::string upload_folder = getUploadFolder(context, path);

	if (access(path.c_str(), F_OK) == -1)
		throw (ErrorException(404));
	else if (path[path.size() - 1] == '/' || access(path.c_str(), W_OK) == -1)
		throw (ErrorException(403));
	if (!client_req.getHeader().at("content-type")[0].compare(0, 30,"multipart/form-data; boundary="))
		post_multipart_form(response, client_req, upload_folder);
	if (*context.getDirective("cgi").begin() == "on" and requiresCGI(path))
	{
		executeCGI(client_req, path, generateEnvp(client_req, context, path));
		response.setCGI(true);
	}
	response.setLocation(path);
	return (m_body);
}

const std::vector<char>	&BodyMaker::deleteMethod(Response &response,
												 const Context& context,
												 std::string path,
												 const ClientRequest& client_req)
{
	if (access(path.c_str(), F_OK) == -1)
		throw (ErrorException(404));
	else if (path[path.size() - 1] == '/' || access(path.c_str(), W_OK) == -1)
		throw (ErrorException(403));
	if (*context.getDirective("cgi").begin() == "on" and requiresCGI(path))
	{
		executeCGI(client_req, path, generateEnvp(client_req, context, path));
		response.setCGI(true);
		return (m_body);
	}
	if (std::remove(path.c_str())) 
		throw (ErrorException(500));
	else
		response.setHttpCode(204);
	return (m_body);
}

const std::vector<char> &BodyMaker::createBody(Response& response)
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
	std::ifstream file(path.c_str());
	if (not file.good())
		throw ErrorException(503);
	m_body = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
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
		close(STDIN_FILENO);
	
		std::vector<char> copy(client_req.getBody());
		copy.push_back('\0');
		std::FILE* tmpf = std::tmpfile();
		std::fputs(&copy[0], tmpf);
		std::rewind(tmpf);
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
		for (int i = 0 ; envp[i] != NULL ; i++)
			free(envp[i]);
		free(envp);
		waitpid(pid, &stat, 0);
		stat = WEXITSTATUS(stat);
		if (stat != 0)
			throw ErrorException(500);
		close(fd[1]);
		int	 ret = 0;
		std::vector<char> buff(1024, 0);
		while ((ret = read(fd[0], &buff[0], 1024)) > 0)
			m_body.insert(m_body.end(), buff.begin(), buff.begin() + ret);
		if (ret < 0)
			throw ErrorException(500);
		close(fd[0]);
	}
}

const std::vector<char> &BodyMaker::autoIndex(std::string &path)
{
	DIR*			dir;
	struct dirent*	dirent;
	char			buff[1024];
	std::string		add_str_to_body;

	path.insert(0, getcwd(buff, 1024) + std::string("/"));
	dir = opendir(path.c_str());
	if (dir == NULL)
		throw ErrorException(404);
	add_str_to_body = "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"utf-8\" />\n\t\t<title>\n\t\t\tAUTOINDEX\n\t\t</title>\n\t</head>\n\n\t<body>\n\t\t<h2>\n\t\t\tWEBSERV AUTOINDEX: ";
	add_str_to_body += path;
	add_str_to_body += "\n\t\t</h2>\n";
    while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_type == DT_DIR)
			add_str_to_body += "\t\t<h4 style=\"color:blue;\"><a href=\"";
		else
			add_str_to_body += "\t\t<h4 style=\"color:black;\"><a href=\"";
		add_str_to_body += dirent->d_name;
		if (dirent->d_type == DT_DIR)
			add_str_to_body += "/";
		add_str_to_body += "\">\n\t\t\t";
		add_str_to_body += dirent->d_name;
		add_str_to_body += "\n\t\t</a></h4>\n";
	}
	closedir(dir);
	add_str_to_body += "\t</body>\n</html>";
	m_body.insert(m_body.end(), add_str_to_body.begin(), add_str_to_body.end());
	return m_body;
}
