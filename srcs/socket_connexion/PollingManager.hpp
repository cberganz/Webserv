#ifndef POLLING_MANAGER_HPP
# define POLLING_MANAGER_HPP

# include <sys/epoll.h>  
# include <vector>
# include <sys/socket.h>
# include <string>
# include <netinet/in.h>
# include <unistd.h>
# include <cstring>
# include <fcntl.h>
# include <iostream>

# include "../config_lexer_parser/Config.hpp"
# include "../tools/utility.hpp"
# include "Chunks.hpp"

# define INITSOCKERR            "Socket() failed."
# define SETSOCKOPTERR          "setsockopt() failed."
# define FCNTLERR               "fcntl() failed : could not set socket to be non blocking."
# define BINDERR                "bind() failed."
# define LISTENERR              "listen() failed."
# define EPOLLCREATEERR         "epoll_create() failed."
# define EPOLLCTLERR            "epoll_ctl() failed."
# define EPOLLWAITERR           "epoll_wait() failed."
# define ACCEPTERR              "accept() failed."
# define RECEIVEERR             "receive() failed."
# define SENDERR                "send() failed."
# define IPERR                "Wrong Ip address format."

# define MAXBUF 8192
# define MAX_EVENTS 5

typedef struct sockaddr_in  t_sockaddr_in;

class PollingManager {
    protected:
        int                 m_epfd;
        std::vector<int>    m_sockets_fds;
        struct epoll_event  m_ready_events[MAX_EVENTS];

    private:
        /** CREATION DE LA CONNEXION **/
        t_sockaddr_in   init_address_structure(int port, int ip);
        int             create_socket(int port, int ip);
        void            close_socket_fds();
        void            set_socket(int fd);
        void            add_socket_to_epoll(int fd);
        uint32_t        getIntIp(std::string string_ip);
        
        class SocketCreationException : public std::exception {
            private:
                std::string m_msg;

            public:
                SocketCreationException(std::string msg);
                ~SocketCreationException() throw();
                const char *what() const throw();
        };
    
    public:
        PollingManager();
        PollingManager(const Context::contextsContainer &container);
        PollingManager(const PollingManager &copy);
        ~PollingManager();
        PollingManager  &operator=(const PollingManager &copy);

        /** EPOLL - TRAITEMENT DES REQUETES **/
        void                                new_client_connexion(int fd);
        void                                send_response(std::string header, int fd);
        void                                init_epoll_events();
        void                                edit_socket_in_epoll(int fd, int event);
        int                                 wait_for_connexions();
        bool                                is_existing_server_socket_fd(int fd);
        int                                 accept_connexion(int ready_fd);
        std::vector<char>                   receive_request(int client_socket);
        void                                send_response(std::vector<char> request, int client_socket);
        void                                close_epfd();
        struct epoll_event                  get_ready_event( int index ) const;
};

#endif
