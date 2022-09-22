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

# include "PollingManager.hpp"

class ServerConnexion {
    protected:
        PollingManager  m_polling;
    public:
        ServerConnexion();
        ServerConnexion(std::vector<int> ports); // remplacer par l'objet parseconfig
        ServerConnexion(const ServerConnexion &copy);
        ~ServerConnexion();
        ServerConnexion &operator=(const ServerConnexion &copy);
        void    connexion_loop();

};

#endif