#ifndef SERVERTYPES_HPP
# define SERVERTYPES_HPP

typedef std::map<int, Server>			serverMap;
typedef serverMap::iterator				serverIterator;
typedef serverMap::const_iterator		serverConstIterator;
typedef Location::locationMap			locationMap;
typedef Location::locationIterator		locationIterator;
typedef Location::locationConstIterator	locationConstIterator;

using typename AContext::tokensVector;
using typename AContext::tokensIterator;
using typename AContext::tokensConstIterator;
using typename AContext::directiveMap;
using typename AContext::directiveIterator;
using typename AContext::directiveConstIterator;

#endif
