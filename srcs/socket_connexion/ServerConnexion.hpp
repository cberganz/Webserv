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
# include <iostream>
# include <exception>

# include "../config_lexer_parser/Config.hpp"
# include "../response/ResponseHandler.hpp"
# include "../tools/utility.hpp"
# include "PollingManager.hpp"
# include "Chunks.hpp"
# include <csignal>

class ServerConnexion {
    private:
        void                write_to_client(int fd);
        void                read_from_client(int fd);

        std::string     	getSocketPort(int sockfd);
        std::string     	getSocketIp(int sockfd);
        void            	handleResponse(std::vector<char> client_req, int fd);
        void            	handleDefaultError(ErrorException & e, int fd);
		std::vector<char>	createDefaultErrorPage(std::string file, std::string status_code, std::string msg);
        bool            	is_size_chunk(std::vector<char> chunk);
        bool            	is_last_request_chunk(std::vector<char> client_req, int fd);

    protected:
        Config			m_config;
        PollingManager  m_polling;
        Chunks          m_chunks;
        ResponseHandler m_rep_handler;

    public:
        ServerConnexion();
        ServerConnexion(const std::string &path);
        ServerConnexion(const ServerConnexion &copy);
        ~ServerConnexion();
        ServerConnexion &operator=(const ServerConnexion &copy);

        void                connexion_loop();
};

#endif
