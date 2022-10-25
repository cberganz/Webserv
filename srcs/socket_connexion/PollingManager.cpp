#include "PollingManager.hpp"

/** NORME DE COPLIEN **/

PollingManager::PollingManager()  : m_epfd(-1) {}

PollingManager::PollingManager(const Context::contextsContainer &container) : m_epfd(-1)
{
    try {
        for (Config::contextsConstIterator it = container.begin() ; it != container.end() ; it++)
        {
            m_sockets_fds.push_back(create_socket(ft::lexical_cast<int>(*(*it).second.getDirective("port").begin()),
                getIntIp(*(*it).second.getDirective("ip").begin())));
        }
    }
    catch (const std::exception &e) {
        throw (SocketCreationException(LISTENERR));
    }
}

PollingManager::PollingManager(const PollingManager &copy) : m_epfd(-1) {
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

/** CREATION DE LA CONNEXION **/

t_sockaddr_in  PollingManager::init_address_structure(int port, int ip) {
    t_sockaddr_in serv_addr;

    std::memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl ( ip );
    serv_addr.sin_port = htons( port );
    return (serv_addr);
}

void            PollingManager::set_socket(int fd) {
    int    on = 1;

    if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, 
                    &on, sizeof(int)) < 0) {
        throw (SocketCreationException(SETSOCKOPTERR));
    }
}

int PollingManager::create_socket(int port, int ip) {
    int             listen_fd = -1;
	t_sockaddr_in   serv_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0)
        throw (SocketCreationException(INITSOCKERR));
    set_socket(listen_fd);
    serv_addr = init_address_structure(port, ip);
    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        throw (SocketCreationException(BINDERR));
    }
    if (listen(listen_fd, 100) < 0) {
        throw (SocketCreationException(LISTENERR));
    }
    return (listen_fd);
}

/** EPOLL CONFIG **/

void                PollingManager::add_socket_to_epoll(int fd) {
    struct epoll_event conf_event;

    memset((char *)&conf_event, 0, sizeof(conf_event)); 
    conf_event.events = EPOLLIN | EPOLLRDHUP;
    conf_event.data.fd = fd;
    if (epoll_ctl(m_epfd, EPOLL_CTL_ADD, conf_event.data.fd, &conf_event) == -1) {
        throw (SocketCreationException(EPOLLCTLERR));
    }
}

void                PollingManager::edit_socket_in_epoll(int fd, int event) {
    struct epoll_event conf_event;

    memset((char *)&conf_event, 0, sizeof(conf_event)); 
    conf_event.events = event | EPOLLRDHUP;
    conf_event.data.fd = fd;
    if (epoll_ctl(m_epfd, EPOLL_CTL_MOD, conf_event.data.fd, &conf_event) == -1) {
        throw (SocketCreationException(EPOLLCTLERR));
    }
}

void            PollingManager::init_epoll_events() {
    if ((m_epfd = epoll_create(10)) < 0){
        throw (SocketCreationException(EPOLLCREATEERR));
    }
	for (size_t i = 0; i < m_sockets_fds.size(); i++)
        add_socket_to_epoll(m_sockets_fds[i]);
}


/** CONNEXION LOOP **/

void               PollingManager::new_client_connexion(int fd) {
    int new_socket = accept_connexion(fd);

    set_socket(new_socket);
    add_socket_to_epoll(new_socket);
}

int             PollingManager::wait_for_connexions() {
    int nfds = epoll_wait(m_epfd, m_ready_events, MAX_EVENTS, 5000);

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

std::vector<char>     PollingManager::receive_request(int client_socket) {
    std::vector<char>   buffer(MAXBUF, '\0');
    int                 ret;

    if ((ret = recv(client_socket, &buffer[0], buffer.size(), 0)) < 0) 
        throw (SocketCreationException(RECEIVEERR));
    buffer.resize(ret);
    return (buffer);
}

void            PollingManager::send_response(std::vector<char> request, int client_socket) {
    if (send(client_socket, &request[0], request.size(), 0) <= 0)
        throw (SocketCreationException(SENDERR));
}

void           PollingManager::close_epfd() {
    close(m_epfd);
    m_epfd = -1;
}

/** UTILS **/

struct epoll_event  PollingManager::get_ready_event( int index ) const
{ return (m_ready_events[index]); }

bool                PollingManager::is_existing_server_socket_fd(int fd) {
    for (std::vector<int>::iterator it = m_sockets_fds.begin(); it != m_sockets_fds.end(); it++) {
        if (fd == *it)
            return (true);
    }
    return (false);
}

uint32_t        PollingManager::getIntIp(std::string string_ip)
{
    uint32_t            ip_val = 0;
    std::istringstream  str_stream(string_ip);
	std::string			line;

	for (unsigned int i = 0; i < 4; i++)
	{
		getline(str_stream, line, '.');
		if (line.empty() || !str_stream)
            throw (SocketCreationException(IPERR));
        ip_val += (ft::lexical_cast<uint32_t>(line) << 8 * (3 - i));
	}
    return (ip_val);
}

/** EXCEPTIONS **/

PollingManager::SocketCreationException::SocketCreationException(std::string msg) : m_msg(msg) {}

PollingManager::SocketCreationException::~SocketCreationException() throw() {}

const char *PollingManager::SocketCreationException::what() const throw() {
    return (m_msg.c_str());
}