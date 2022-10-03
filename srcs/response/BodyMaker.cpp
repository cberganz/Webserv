/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:55:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/03 03:00:34 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BodyMaker.hpp"

BodyMaker::BodyMaker()
{}

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

const std::string &BodyMaker::createBody(const std::string &path)
{
	m_body.clear();
	if (access(path.c_str(), F_OK) == -1)
		throw ErrorException(404);
	if (requiresCGI(path))
		executeCGI(path);
	else
		readFile(path);
	return m_body;
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

void BodyMaker::executeCGI(const std::string &path)
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