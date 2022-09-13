#ifndef ACONTEXTTYPES_HPP
# define ACONTEXTTYPES_HPP

typedef std::map<std::string, std::string>	directiveMap;
typedef directiveMap::iterator				directiveIterator;
typedef directiveMap::const_iterator		directiveConstIterator;
typedef std::vector<std::string>			tokensVector;
typedef tokensVector::iterator				tokensIterator;
typedef tokensVector::const_iterator		tokensConstIterator;

#endif
