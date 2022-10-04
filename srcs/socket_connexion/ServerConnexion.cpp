#include "ServerConnexion.hpp"

ServerConnexion::ServerConnexion() : m_polling(), m_config() {}

ServerConnexion::ServerConnexion(const std::string &path)
	: m_config(path),
	  m_polling(m_config.getGlobalContextsContainer())
{}

ServerConnexion::ServerConnexion(const ServerConnexion &copy) {
    if (this != &copy)
        *this = copy;
}

ServerConnexion::~ServerConnexion() {

}

ServerConnexion &ServerConnexion::operator=(const ServerConnexion &copy) {
    if (this != &copy)
    {
        m_polling = copy.m_polling;
    }
    return (*this);
}

void    ServerConnexion::connexion_loop()
{
    m_polling.init_epoll_events();
    while(1)
    {
        int nfds;
        nfds = m_polling.wait_for_connexions();// throw?

		for(int i = 0; i < nfds; i++) {
            struct epoll_event  event;

            event = m_polling.get_ready_event(i);
            // erreur ou hangup dans la connexion client
            if ((event.events & EPOLLERR) || (event.events & EPOLLHUP) ||
                (!(event.events & EPOLLIN) && !(event.events & EPOLLOUT))) 
                close (event.data.fd);

            // nouvelle connexion client
            else if (m_polling.is_existing_socket_fd(event.data.fd))
                m_polling.new_client_connexion(event.data.fd);
            
            // data dispo pour la lecture dans une connexion client
            else if (event.events & EPOLLIN) 
                m_polling.epoll_event_epollin(event.data.fd, m_chunks);
            
            // socket client dispo pour l'ecriture
            else if (event.events & EPOLLOUT)
                m_polling.epoll_event_epollout(m_chunks.get_next_chunk(event.data.fd), event.data.fd);
		}
    }
	m_polling.close_epfd();
}
