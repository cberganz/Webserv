/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AContext.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:10:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/09/12 18:20:46 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACONTEXT_HPP
# define ACONTEXT_HPP

# include <utility>
# include <iostream>
# include <iomanip>
# include <map>
# include "Lexer.hpp"
//# include "GlobalContext.hpp"
//# include "Server.hpp"
//# include "Location.hpp"

# define UNAVAILABLE_DIRECTIVE "Directive does not exists in this context."
# define MANDATORY_DIRECTIVE_NOT_FOUND "Context mandatory directive not found."
# define NO_SEMICOLON "Directive ends without semicolon."
# define NO_BLOC_OPEN "Bloc starts without opening bracket (\'{\')."
# define UNEXPECTED_EOF "Reached unexpected EOF while looking for bloc closing bracket (\'}\')."

class GlobalContext;
class Server;
class Location;

class AContext {

public:
	typedef Lexer::vector						lexerVector;
	typedef Lexer::iterator						lexerIterator;
	typedef std::map<std::string, std::string>	directiveMap;
	typedef directiveMap::iterator				directiveIterator;
	typedef std::map<int, Server>				serverMap;
	typedef serverMap::iterator					serverIterator;
	typedef std::map<std::string, Location>		locationMap;
	typedef locationMap::iterator				locationIterator;

	AContext();
	virtual ~AContext() = 0;

private:
	std::string m_contextName;

	bool keywordExistsInContext(const std::string *context, const std::string &keyword);
	bool checkMandatoryDirectives(const std::string *context, directiveMap &directives);

	class ParsingErrorException : public std::exception
    {
		private:
			const std::string message;

        public:
			ParsingErrorException(const AContext &context, const char *errorDetails)
				: message("Error while parsing configuration file: Inside context: "
						  + context.m_contextName
						  + ": " + errorDetails)
			{}

			~ParsingErrorException() throw() {}

    	    const char* what() const throw()
    	    { return message.c_str(); }
    };

};

#endif
