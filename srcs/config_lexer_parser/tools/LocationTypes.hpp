#ifndef LOCATIONTYPES_HPP
# define LOCATIONTYPES_HPP

typedef std::map<std::string, Location>	locationMap;
typedef locationMap::iterator			locationIterator;
typedef locationMap::const_iterator		locationConstIterator;

using typename AContext::tokensVector;
using typename AContext::tokensIterator;
using typename AContext::tokensConstIterator;
using typename AContext::directiveMap;
using typename AContext::directiveIterator;
using typename AContext::directiveConstIterator;

#endif
