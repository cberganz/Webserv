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

# define INITSOCKERR            "Socket() failed."
# define SETSOCKOPTERR          "setsockopt() failed."
# define FCNTLERR               "fcntl() failed : could not set socket to be non blocking."
# define BINDERR                "bind() failed."
# define LISTENERR              "listen() failed."
# define EPOLLCREATEERR         "epoll_create() failed."
# define EPOLLWAITERR           "epoll_wait() failed."
# define ACCEPTERR              "accept() failed."
# define RECEIVEERR             "receive() failed."
# define SENDERR                "send() failed."

# define MAXBUF 8192
# define MAX_EVENTS 5

typedef struct sockaddr_in  t_sockaddr_in;// voir la bonne position

class PollingManager {
    protected:

        int                 m_epfd;
        std::vector<int>    m_sockets_fds;
        struct epoll_event  m_ready_events[MAX_EVENTS];

    private:
        /** CREATION DE LA CONNEXION **/
        t_sockaddr_in   init_address_structure(int port);
        int             create_socket(int port);
        void            close_socket_fds();
        
        class SocketCreationException : public std::exception {
            private:
                std::string m_msg;

            public:
                SocketCreationException(std::string msg);
                ~SocketCreationException();
                const char *what() const throw();
        };
    
    public:
        PollingManager();
        PollingManager(const std::vector<int> ports);
        PollingManager(const PollingManager &copy);
        ~PollingManager();
        PollingManager  &operator=(const PollingManager &copy);

        /** EPOLL - TRAITEMENT DES REQUETES **/
        void                init_epoll_events();
        int                 wait_for_connexions();
        int                 accept_connexion(int ready_fd);
        std::string         receive_request(int client_socket);
        void                send_request(std::string request, int client_socket);
        void                close_epfd();
        struct epoll_event  get_ready_event( int index ) const;

};

#endif