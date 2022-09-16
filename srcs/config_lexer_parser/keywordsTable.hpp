#ifndef KEYWORDSTABLE_HPP
# define KEYWORDSTABLE_HPP

# include <string>

/*
**	@brief This configuration file defines the behaviour of the Parser class.
**
**	The Parser class is built on a fully compliant way depending on the following
**	parameters making it possible to easily adjust the way the server configurat-
**	ion file will be parsed.
*/

/*
**	@brief Enum of the contexts allowed in the server configuration file.
**	@category Enum
**
**	The contexts enum allows you to add or remove the contexts that can be reac-
**	hed in the server configuration file. Any change to this contexts enum MUST
**	be accompanied by a re-implementation of the keywords table.
*/

enum contexts {
	GLOBAL,			//.................Stands for GLOBAL context position in the keywords table..............
	SERVER,			//.................Stands for SERVER context position in the keywords table..............
	LOCATION,		//.................Stands for LOCATION context position in the keywords table............
	CONTEXTS_COUNT	//.................Defines the total number of existing contexts.........................
};

/*
**	@brief String array allowing constructor to perform string convertion
**		   to context enum index.
**	@category std::string array
**
**	For abstraction purpose in the Context class, string convertion to context
**	enum index is performed while contructing a ParserConfig object. This array
**	MUST be updated with any change in the context enum and keywords table. The
**	order of the strings must be the same as the enum.
*/

const std::string enumIndexes[] = {
	"global",
	"server",
	"location",
	""
};

/*
**	@brief Structure containing the settings for a specified keyword.
**	@category Structure
*/

typedef struct s_keywords {
	std::string		keyword;	//.....Defines the keyword as a string......................................
	bool			mandatory;	//.....Defines whether the keyword is mandatory in the context..............
	bool			possible;	//.....Defines whether the keyword is possible in the context...............
	bool			isDirective;//.....Defines whether the keyword represents a directive...................
	bool			isBlock;	//.....Defines whether the keyword represents a new block...................
	bool			hasUri;		//.....Defines whether an URI is neccessary for a bloc (ie. for location)...
}	t_keywords;

/*
**	@brief	 Defines the maximum number of keywords a context can contain inside
**		     the keyword table.
**	@warning This MUST be changed when adding new keywords to the table.
*/

# define MAX_KEYWORDS 6

/*
**	@brief Two dimensional array containing possible and/or mandatory directives
**		   and blocks inside any context specified in the contexts enum, and the
**		   corresponding settings.
**	@category Two dimensional array
**
**	The first dimension represents the contexts listed in the contexts enum. In
**	the case of adding a context it is necessary to implement it inside the tab-
**	le. The second dimension contains the instances of the s_keywords structure.
*/

const t_keywords keywords[CONTEXTS_COUNT][MAX_KEYWORDS] = {

	{   /*..........................GLOBAL CONTEXT........................*/
	    /*.Keyword.....Mandatory...Possible..IsDirective..IsBlock..hasUri.*/
		{ "server",		false,		true,		false,		true,	false }, //.....Sets configuration for a virtual server................
		{ "root",		false,		true,		true,		false,	false }, //.....Sets the root directory for requests...................
		{ "",			false,		false,		false,		false,	false }, //.....Default settings if no keyword was found...............
	},

	{   /*..........................SERVER CONTEXT........................*/ 
	    /*.Keyword.....Mandatory...Possible..IsDirective..IsBlock..hasUri.*/ 
		{ "location",	false,		true,		false,		true,	true  }, //.....Sets configuration depending on a request URI..........
		{ "root",		true,		true,		true,		false,	false }, //.....Sets the root directory for requests...................
		{ "listen",		true,		true,		true,		false,	false }, //.....Sets address:port IP, or the UNIX-domain socket path...
		{ "server_name",false,		true,		true,		false,	false }, //.....Sets names of a virtual server.........................
		{ "index",		false,		true,		true,		false,	false }, //.....Defines files that will be used as an index............
		{ "",			false,		false,		false,		false,	false }, //.....Default settings if no keyword was found...............
	},

	{   /*.........................LOCATION CONTEXT.......................*/ 
	    /*.Keyword.....Mandatory...Possible..IsDirective..IsBlock..hasUri.*/ 
		{ "root",		true,		true,		true,		false,	false }, //.....Sets the root directory for requests...................
		{ "index",		true,		true,		true,		false,	false }, //.....Defines files that will be used as an index............
		{ "",			false,		false,		false,		false,	false }, //.....Default settings if no keyword was found...............
	},

};

#endif
