#ifndef SERVER_HPP
# define SERVER_HPP

# include "AContext.hpp"

class Server : public AContext {

public:

private:
	locationMap		m_locations;
	directiveMap	m_serverDirectives;

};

#endif
