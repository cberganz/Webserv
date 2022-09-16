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
	ParserConfig(const std::string &contextName);
	~ParserConfig();

protected:
	int				  m_contextIndex;
	const std::string m_contextName;

	int	getIndex(const std::string &keyword);
	int	getContextIndex(const std::string &context);
	
	bool isPossible(const std::string &keyword);
	bool isMandatory(const std::string &keyword);
	bool isDirective(const std::string &keyword);
	bool isBlock(const std::string &keyword);

	bool isPossibleDirective(const std::string &keyword);
	bool isMandatoryDirective(const std::string &keyword);
	bool isPossibleBlock(const std::string &keyword);
	bool isMandatoryBlock(const std::string &keyword);

	bool contextNameRequiresURI(const std::string &parentContext, const std::string &context);
	bool contextNameRequiresURI(const std::string &context);

};

#endif
