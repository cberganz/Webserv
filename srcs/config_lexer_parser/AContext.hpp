/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContext.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/14 01:33:52 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACONTEXT_HPP
# define ACONTEXT_HPP

# include <utility>
# include <iostream>
# include <iomanip>
# include <vector>
# include <map>
# include "tools/parsingErrors.hpp"

class AContext {

public:
	#include "tools/AContextTypes.hpp"

	AContext(const std::string &contextName, const int &contextNumber);
	virtual ~AContext();

protected:
	const std::string	m_contextName;
	const int			m_contextNumber;

	bool keywordExistsInContext(const std::string *context, const std::string &keyword);
	bool checkMandatoryDirectives(const std::string *context, directiveMap &directives);

	template <typename ContainerType, typename KeyType, typename ValueType>
	void containerReplaceInserter(ContainerType &container, const KeyType &oldValueKey, const ValueType &newValue)
	{
		container.erase(oldValueKey);
		container.insert(newValue);
	}

	class ParsingErrorException : public std::exception
    {
		private:
			const std::string message;

        public:
			ParsingErrorException(const AContext &context, const char *errorDetails, const std::string &token)
				: message("Error while parsing configuration file: Inside context: "
						  + context.m_contextName
						  + ": " + errorDetails
						  + ": \'" + token + "\'.")
			{}

			~ParsingErrorException() throw() {}

    	    const char* what() const throw()
    	    { return message.c_str(); }
    };

};

#endif
