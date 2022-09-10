#ifndef SERVER_HPP
# define SERVER_HPP

class Server {

public:
	typedef std::map<std::string, Location>	locationMap;
	typedef locationMap::iterator			locationIterator;

private:
	locationMap	m_locations;

};

#endif
