#ifndef ACONTEXT_HPP
# define ACONTEXT_HPP

# include <utility>
# include <iostream>
# include <iomanip>
# include <map>

# define UNAVAILABLE_DIRECTIVE "Directive does not exists in this context."
# define NO_SEMICOLON "Directive ends without semicolon."

class AContext {

public:
	typedef std::map<std::string, std::string>	directiveMap;
	typedef std::map<int, Server>				serverMap;
	typedef serverMap::iterator					serverIterator;
	typedef std::map<std::string, Location>		locationMap;
	typedef locationMap::iterator				locationIterator;

	AContext();
	virtual ~AContext() = 0;

private:
	std::string m_contextName;

	bool keywordExistsInContext(const std::string *context, const std::string &keyword);

	class ParsingErrorException : public std::exception
    {
		private:
			const std::string message;

        public:
			ParsingErrorException(const AContext &context, const char *errorDetails)
				: message("Error while parsing configuration file: Inside context: "
						  + context->m_contextName
						  + ": " + errorDetails)
			{}

    	    const char* what() const throw()
    	    { return message.c_str(); }
    };	

};

#endif
