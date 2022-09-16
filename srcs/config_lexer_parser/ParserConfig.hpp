/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:29 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/16 17:12:31 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERCONFIG_HPP
# define PARSERCONFIG_HPP

# include <string>
# include <stdexcept>
# include "parsingErrors.hpp"
# include "keywordsTable.hpp"

/*
**	@brief This class allows the Parser class to read informations from the key-
**		   -words table and adapt its behaviour depending on it.
**	@category class
*/

class ParserConfig {

public:
	ParserConfig();
	ParserConfig(const ParserConfig &src);
	ParserConfig(const std::string &contextName, const std::string &parentContext);
	~ParserConfig();

	ParserConfig &operator=(const ParserConfig &rhs);

	const int		  &getContextIndex() const;
	const std::string &getContextName() const;
	const std::string &getParentName() const;

protected:
	int			m_contextIndex;
	std::string	m_contextName;
	std::string	m_parentName;

	int	getIndex(const std::string &keyword);
	int	getContextIndex(const std::string &context);

	bool isPossible(const std::string &keyword);
	bool isMandatory(const std::string &keyword);
	bool isDirective(const std::string &keyword);
	bool isBloc(const std::string &keyword);

	bool isPossibleDirective(const std::string &keyword);
	bool isMandatoryDirective(const std::string &keyword);
	bool isPossibleBloc(const std::string &keyword);
	bool isMandatoryBloc(const std::string &keyword);

	bool contextNameRequiresURI(const std::string &parentContext, const std::string &context);
	bool contextNameRequiresURI(const std::string &context);

};

#endif
