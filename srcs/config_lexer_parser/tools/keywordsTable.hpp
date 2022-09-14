#ifndef KEYWORDSTABLE_HPP
# define KEYWORDSTABLE_HPP

/*
**	@brief This configuration file defines the behaviour of the Parser class.
**
**	The Parser class is built on a fully compliant way depending on the following
**	parameters making it possible to easily adjust the way the server configuration
**	file will be parsed.
**
*/

/*
**	@brief Enumeration of the contexts allowed in the server configuration file.
**	@category Enum
**
**	The contexts enum allows you to add or remove the contexts that can be reached
**	in the server configuration file. Any change to this contexts enum MUST be
**	accompanied by a re-implementation of the keywords table.
*/

enum contexts {
	GLOBAL,			/*...............................................Stands for GLOBAL context position in the keywords array.................*/
	SERVER,			/*...............................................Stands for SERVER context position in the keywords array.................*/
	LOCATION,		/*...............................................Stands for LOCATION context position in the keywords array...............*/
	CONTEXTS_COUNT	/*...............................................Defines the total number of existing contexts............................*/
};

/*
**	@brief Structure containing the settings for a specified keyword.
**	@category Structure
*/

typedef struct s_keywords {
	std::string		keyword;	/*...................................Defines the keyword as a string..........................................*/
	bool			mandatory;	/*...................................Defines whether the keyword is mandatory in the context..................*/
	bool			possible;	/*...................................Defines whether the keyword is possible in the context...................*/
	bool			newBlock;	/*...................................Defines whether the keyword represents a new block.......................*/
}	t_keywords;

/*
**	@brief Two dimensional array containing possible and/or mandatory directives
**		   and blocks inside any context specified in the contexts enum.
**	@category Two dimensional array
**
**	The first dimension represents the differents contexts listed in the contexts
**	enum. In the case of adding a context it is necessary to implement it inside
**	the table. The second dimension contains the instances of the s_keywords structure.
*/

const t_keywords keywords[CONTEXTS_COUNT][] = {

	{  /*..................GLOBAL CONTEXT..................*/
	   /*.Keyword.........Mandatory....Possible....IsBlock.*/
		{ "server",			false,		true,		true  },	/*...Sets configuration for a virtual server..................................*/
		{ "root",			false,		true,		false },	/*...Sets the root directory for requests.....................................*/
		{ "",				false,		false,		false },	/*...Default settings if no keyword was found.................................*/
	},

	{  /*..................SERVER CONTEXT..................*/
	   /*.Keyword.........Mandatory....Possible....IsBlock.*/
		{ "location",		false,		true,		true  },	/*...Sets configuration depending on a request URI............................*/
		{ "root",			true,		true,		false },	/*...Sets the root directory for requests.....................................*/
		{ "listen",			true,		true,		false },	/*...Sets the address and port for IP, or the path for a UNIX-domain socket...*/
		{ "server_name",	false,		true,		false },	/*...Sets names of a virtual server...........................................*/
		{ "index",			false,		true,		false },	/*...Defines files that will be used as an index..............................*/
		{ "",				false,		false,		false },	/*...Default settings if no keyword was found.................................*/
	},

	{  /*.................LOCATION CONTEXT.................*/
	   /*.Keyword.........Mandatory....Possible....IsBlock.*/
		{ "root",			true,		true,		false },	/*...Sets the root directory for requests.....................................*/
		{ "index",			true,		true,		false },	/*...Defines files that will be used as an index..............................*/
		{ "",				false,		false,		false },	/*...Default settings if no keyword was found.................................*/
	},

};

#endif
