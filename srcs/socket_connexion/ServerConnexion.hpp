#ifndef SERVERCONNEXION_HPP
# define SERVERCONNEXION_HPP

# include <stdio.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <string.h>
# include <string>
# include <fstream>
# include <iostream>
# include <vector>
# include <sys/epoll.h>  
# include <fcntl.h>
# include <errno.h>
# include <exception>

# include "../config_lexer_parser/Config.hpp"
# include "PollingManager.hpp"
# include "Chunks.hpp"

class ServerConnexion {

protected:
	Config			m_config;
    PollingManager  m_polling;
    Chunks          m_chunks;

public:
    ServerConnexion();
    ServerConnexion(const std::string &path);
    ServerConnexion(const ServerConnexion &copy);
    ~ServerConnexion();
    ServerConnexion &operator=(const ServerConnexion &copy);
    void    connexion_loop();

};

#endif
