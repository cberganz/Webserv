/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:29 by cberganz          #+#    #+#             */
/*   Updated: 2022/10/26 13:54:58 by rbicanic         ###   ########.fr       */
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
	ParserConfig(const std::string &contextName,
				 const std::string &parentContext);
	~ParserConfig();

	ParserConfig &operator=(const ParserConfig &rhs);

	const int		  &getContextIndex() const;
	const std::string &getContextName() const;
	const std::string &getParentName() const;

protected:
	int			m_contextIndex;
	std::string	m_contextName;
	std::string	m_parentName;

	bool isPossible(const std::string &keyword) const;
	bool isMandatory(const std::string &keyword) const;
	bool isDirective(const std::string &keyword) const;
	bool isBloc(const std::string &keyword) const;
	bool hasDefault(const std::string &keyword) const;
	bool isPossibleDirective(const std::string &keyword) const;
	bool isMandatoryDirective(const std::string &keyword) const;
	bool isPossibleBloc(const std::string &keyword) const;
	bool isMandatoryBloc(const std::string &keyword) const;
	bool isMultiple(const std::string &keyword) const;

	const std::string &getKeyword(const int &index) const;
	const std::string &getDefault(const int &index) const;
	bool isPossible(const int &index) const;
	bool isMandatory(const int &index) const;
	bool isDirective(const int &index) const;
	bool isBloc(const int &index) const;
	bool hasDefault(const int &index) const;
	bool isPossibleDirective(const int &index) const;
	bool isMandatoryDirective(const int &index) const;
	bool isPossibleBloc(const int &index) const;
	bool isMandatoryBloc(const int &index) const;
	bool isMultiple(const int &index) const;

	bool indexIsDefault(const int &index) const;

	bool indexMatchKeyword(const int &index,
						   const std::string &keyword) const;

	bool contextNameRequiresURI(const std::string &context) const;
	bool contextNameRequiresURI(const std::string &parentContext,
								const std::string &context);

private:
	int	getKeywordIndex(const std::string &keyword) const;
	int	getContextIndex(const std::string &context) const;

}; // class ParserConfig

#endif // PARSERCONFIG_HPP
