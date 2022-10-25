/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseMaker.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:04:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/25 20:30:33 by rbicanic         ###   ########.fr       */
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
	  m_bodyMaker(config)
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
	if (std::toupper(max_body_size[max_body_size.size() - 1]) != 'M')
		throw ErrorException(500); // erreur sur le format de la valeur max body size voir quoi faire
	for (size_t i = 0; i < max_body_size.length() - 1; i++)
		if (!std::isdigit(max_body_size[i]))
			throw ErrorException(500); // erreur sur le format de la valeur max body size voir quoi faire
	
	size_t max_size = std::atoi(max_body_size.c_str()) * 1000000;// en mega voir comment fair pour giga etc
	if (client_req.getBody().size() > max_size)
		return (true);
	return (false);
}

Response ResponseMaker::createResponse(ClientRequest &client_req, const Context& server, const std::string& longest_location)
{

	if (not server.contextExist(longest_location))
		throw ErrorException(404);
	Context 	context = server.getContext(longest_location); // WARNING: throw error if uri is not find in server. Throw HTTP error if this case ?
	Response	response(client_req, context, longest_location);

	if (!this->isMethodAllowed(context, client_req))// verifier que directive method peut etre dans location
		throw ErrorException(405);
	if (this->isBodySizeLimitReached(context, client_req))// verifier le bon fonctionnement de la taille
		throw ErrorException(413);
	if (context.directiveExist("rewrite"))
	{
		if (context.getDirective("rewrite").size() < 2
			or !m_httpCodes.codeExist(ft::lexical_cast<int>(context.getDirective("rewrite")[1])))
			throw ErrorException(500);
		response.setHttpCode(ft::lexical_cast<int>(context.getDirective("rewrite")[1]));
		response.setLocation(*context.getDirective("rewrite").begin());
		response.insert(0, m_headerMaker.createHeader(client_req, response));
		return response;
	}

	response.append(m_bodyMaker.createBody(response));
	response.insert(0, m_headerMaker.createHeader(client_req, response));
	return response;
}
