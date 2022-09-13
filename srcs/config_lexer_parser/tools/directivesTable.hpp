#ifndef DIRECTIVESTABLE_HPP
# define DIRECTIVESTABLE_HPP

# define CONTEXTS_COUNT 3	/*....................................Defines the total number of possible contexts...............*/

# define GLOBAL			1	/*....................................Stands for GLOBAL context position in the keywords array....*/
# define SERVER			2	/*....................................Stands for SERVER context position in the keywords array....*/
# define LOCATION		3	/*....................................Stands for LOCATION context position in the keywords array..*/

typedef struct s_keywords {
	const std::string	keyword;   /*.............................Defines the keyword as a string.............................*/
	const bool			mandatory; /*.............................Defines whether the keyword is mandatory in the context.....*/
	const bool			possible;  /*.............................Defines whether the keyword is possible in the context......*/
	const bool			newBlock;  /*.............................Defines whether the keyword represents a new block..........*/
} t_keywords;

const t_keywords keywords[CONTEXTS_COUNT][] = {

	{  /*..................GLOBAL CONTEXT..................*/
	   /*.Directive.......Mandatory...Possible.....IsBlock.*/
		{ "server",			false,		true,		true  },
		{ "root",			false,		true,		false },
		{ "",				false,		false,		false },
	},

	{  /*..................SERVER CONTEXT..................*/
	   /*.Directive.......Mandatory...Possible.....IsBlock.*/
		{ "location",		false,		true,		true  },
		{ "root",			true,		true,		false },
		{ "listen",			true,		true,		false },
		{ "server_name",	false,		true,		false },
		{ "index",			false,		true,		false },
		{ "",				false,		false,		false },
	},

	{  /*.................LOCATION CONTEXT.................*/
	   /*.Directive.......Mandatory...Possible.....IsBlock.*/
		{ "root",			true,		true,		false },
		{ "index",			true,		true,		false },
		{ "",				false,		false,		false },
	},

};

#endif
