#include "PollingManager.hpp"

/** CREATION DE LA CONNEXION **/

t_sockaddr_in  PollingManager::init_address_structure(int port) {
    t_sockaddr_in serv_addr;

    std::memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( port );
    return (serv_addr);
}

int PollingManager::create_socket(int port) {
    int    on = 1;
    int    listen_sd = -1;
	t_sockaddr_in serv_addr;

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
        throw (SocketCreationException(INITSOCKERR));

    serv_addr = init_address_structure(port);
    if (setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, 
                    &on, sizeof(int)) < 0) {
        close(listen_sd);
        throw (SocketCreationException(SETSOCKOPTERR));
    }

    if(fcntl(listen_sd, F_SETFL, O_NONBLOCK) < 0) {
        close(listen_sd);
        throw (SocketCreationException(FCNTLERR));
    }

    if (bind(listen_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        close(listen_sd);
        throw (SocketCreationException(BINDERR));
    }

    if (listen(listen_sd, 100) < 0) {
        close(listen_sd);
        throw (SocketCreationException(LISTENERR));
    }

    return (listen_sd);
}

/** EPOLL - TRAITEMENT DES REQUETES **/
void            PollingManager::init_epoll_events() {
    if ((m_epfd = epoll_create(10)) < 0)
        throw (SocketCreationException(EPOLLCREATEERR));
	for (size_t i = 0; i < m_sockets_fds.size(); i++)
	{
		struct epoll_event conf_event;

		conf_event.events = EPOLLIN;
		conf_event.data.fd = m_sockets_fds[i];
		epoll_ctl(m_epfd, EPOLL_CTL_ADD, conf_event.data.fd, &conf_event);
	}
}

int             PollingManager::wait_for_connexions() {
    std::cout << "\rPollinginit_epoll_events() for input: " << std::flush;

    int nfds = epoll_wait(m_epfd, m_ready_events, MAX_EVENTS, 5000); // check timeoout et MAX_EVENTS -> que mettre ?

    if (nfds == -1) 
        throw (SocketCreationException(EPOLLWAITERR));
    return (nfds);
}

int            PollingManager::accept_connexion(int ready_fd) {
    int new_socket;

    if ((new_socket = accept(ready_fd, NULL, NULL)) < 0)
        throw (SocketCreationException(ACCEPTERR));
    return (new_socket);
}

std::string     PollingManager::receive_request(int client_socket) {
    char    buffer[MAXBUF];
    int     ret;

    if ((ret = recv(client_socket, &buffer, MAXBUF, 0)) < 0) // comment reagir quand la taille est depassee ?
    {
        close(client_socket); // pas sur, peut etre renvoyer une reponse au client
        throw (SocketCreationException(RECEIVEERR));
    }
    buffer[ret] = '\0';
    return (std::string(buffer));
}

void            PollingManager::send_request(std::string request, int client_socket) {
    if(send(client_socket, request.c_str(), request.length(), 0) < 0) {
        close(client_socket);
        throw (SocketCreationException(SENDERR));
    }
}

void           PollingManager::close_epfd() {
    close(m_epfd);
    m_epfd = -1;
}

struct epoll_event  PollingManager::get_ready_event( int index ) const
{ return (m_ready_events[index]); }


/** NORME DE COPLIEN **/

PollingManager::PollingManager() {}

PollingManager::PollingManager(const Context::contextsContainer &container)
{
    for (Config::contextsConstIterator it = container.begin() ; it != container.end() ; it++)
        m_sockets_fds.push_back(create_socket(ft::lexical_cast<int>((*it).second.getDirective("port"))));
}

PollingManager::PollingManager(const PollingManager &copy) {
    if (this != &copy)
        *this = copy;
}

void    PollingManager::close_socket_fds()
{
    for (std::vector<int>::iterator it = m_sockets_fds.begin(); it != m_sockets_fds.end(); it++) {
        close(*it);
    }
}

PollingManager::~PollingManager() {
    close_socket_fds();
    if (m_epfd != -1)
        close_epfd();
}

PollingManager &PollingManager::operator=(const PollingManager &copy) {
    if (this != &copy)
    {
        close_socket_fds();
        m_sockets_fds = copy.m_sockets_fds;
    }
    return (*this);
}

/** EXCEPTIONS **/

PollingManager::SocketCreationException::SocketCreationException(std::string msg) : m_msg(msg) {}

PollingManager::SocketCreationException::~SocketCreationException() {}

const char *PollingManager::SocketCreationException::what() const throw() {
    return (m_msg.c_str());
}
