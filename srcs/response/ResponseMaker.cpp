/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMaker.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:04:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/12 18:50:47 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ResponseMaker.hpp"

ResponseMaker::ResponseMaker()
	: m_httpCodes(),
	  m_config(),
	  m_headerMaker(),
	  m_bodyMaker()
{}

ResponseMaker::ResponseMaker(const Config &config)
	: m_httpCodes(),
	  m_config(config),
	  m_headerMaker(),
	  m_bodyMaker()
{}

ResponseMaker::~ResponseMaker()
{}

ResponseMaker::ResponseMaker(const ResponseMaker &src)
{ *this = src; }

ResponseMaker& ResponseMaker::operator=(const ResponseMaker &rhs)
{
	if (this != &rhs)
	{
		this->m_httpCodes = rhs.m_httpCodes;
		this->m_config = rhs.m_config;
		this->m_headerMaker = rhs.m_headerMaker;
		this->m_bodyMaker = rhs.m_bodyMaker;
	}
	return *this;
}

bool	ResponseMaker::isMethodAllowed(Context &context, ClientRequest &client_req)
{
	if (context.directiveExist("allowed_methods")
		&& context.getDirective("allowed_methods")[0] != "default")// bizarre que ca me donne default quand pas de dir persent
	{
		ContextBase::tokensContainer directives = context.getDirective("allowed_methods");
		if (std::find(directives.begin(), directives.end(), client_req.getMethod())
			== directives.end())
			return (false);
	}
	return (true);
}

bool	ResponseMaker::isBodySizeLimitReached(Context &context, ClientRequest &client_req)
{
	if (!context.directiveExist("client_max_body_size"))
		throw ErrorException(500);
	
	std::string max_body_size = context.getDirective("client_max_body_size")[0];
	if (std::toupper(max_body_size.back()) != 'M')
		throw ErrorException(500); // erreur sur le format de la valeur max body size voir quoi faire
	for (size_t i = 0; i < max_body_size.length() - 1; i++)
		if (!std::isdigit(max_body_size[i]))
			throw ErrorException(500); // erreur sur le format de la valeur max body size voir quoi faire
	
	size_t max_size = std::atoi(max_body_size.c_str()) * 1000000;// en mega voir comment fair pour giga etc
	if (client_req.getBody().size() > max_size)
		return (true);
	return (false);
}

void	ResponseMaker::handleErrorPageDirective(const Context &context, int error_status, const std::string path)
{
	ContextBase::tokensContainer error_page_tokens =
			context.getDirective("error_page");

	if (error_page_tokens.front() == "default")
		throw ErrorException(error_status);

	Lexer::tokensContainer::iterator error_it =
				std::find(error_page_tokens.begin(), error_page_tokens.end(), ft::itostr(error_status));

	if (error_it == error_page_tokens.end()
		|| error_it + 1 == error_page_tokens.end())
			throw ErrorException(error_status);

	std::string error_file_path = path + "/" + *(error_it + 1);

	std::cout << "\n\n"+error_file_path+"\n\n" << std::endl;
	if (access(error_file_path.c_str(), F_OK ) != -1
		&& access(error_file_path.c_str(), R_OK ) != -1)
			throw ErrorException(error_status, error_file_path);

	throw ErrorException(error_status);
}

std::string	ResponseMaker::findLongestLocation(Context context, std::string uri)
{
	while (!uri.empty())
	{
		if (context.contextExist(uri))
			return (uri);
		uri = uri.erase(uri.find_last_of("/"), uri.length() - uri.find_last_of("/"));
	}
	if (context.contextExist("/"))
		return ("/");
	return (uri);
}

Response* ResponseMaker::createResponse(ClientRequest &client_req, const std::string &ip, const std::string &port)
{
	std::string longest_location = findLongestLocation(m_config[ip + ":" + port], client_req.getPath());

	try {
		if (!m_config[ip + ":" + port].contextExist(longest_location))
			throw ErrorException(404);
		Context context = m_config[ip + ":" + port].getContext(longest_location); // WARNING: throw error if uri is not find in server. Throw HTTP error if this case ?
		Response*	response = new Response(client_req, context, longest_location);

		if (!this->isMethodAllowed(context, client_req))// verifier que directive method peut etre dans location
			throw ErrorException(405);
		if (this->isBodySizeLimitReached(context, client_req))// verifier le bon fonctionnement de la taille
			throw ErrorException(413);

		std::string body = m_bodyMaker.createBody(*response);
		(*response).append(m_headerMaker.createHeader());
		(*response).append(body);
		return response;
	} catch (ErrorException &e) {
		Context	context =
			m_config[ip + ":" + port].getContext(longest_location);
		handleErrorPageDirective(context, e.getCode(), *context.getDirective("root").begin());
	}
	return new Response();
}
