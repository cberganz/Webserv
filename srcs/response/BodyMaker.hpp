/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BodyMaker.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:52:22 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/10 19:03:19 by rbicanic         ###   ########.fr       */
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
# include "../client_request/ClientRequest.hpp"
# include "extensionsTable.hpp"
# include <cstdio>

class BodyMaker {

public:
	BodyMaker();
	BodyMaker(const BodyMaker &src);
	~BodyMaker();

	BodyMaker &operator=(const BodyMaker &rhs);

	const std::string &createBody(const Context &context, const ClientRequest& client_req);

private:
	typedef const std::string& (BodyMaker::*MethodFunctions)(const Context&, std::string path, const ClientRequest&);

	std::map<std::string, MethodFunctions>	m_method_fcts;
	std::string 							m_body;
	ClientRequest							m_client_request;

	const std::string &getProgName(const std::string &path);
	bool requiresCGI(const std::string &path);
	void readFile(const std::string &path);
	void executeCGI(std::string &path);
	const std::string &autoIndex(std::string &path);

	/** METHODS **/
	const std::string	&getMethod(const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&postMethod(const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&deleteMethod(const Context& context, std::string path, const ClientRequest& client_req);
	const std::string	&CallMethod( const std::string & s, const Context& context, std::string path, const ClientRequest& client_req);

};

#endif // BODYMAKER_HPP
