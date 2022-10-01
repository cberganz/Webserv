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

// a DELETE
std::string	create_response(std::string file) {
	std::ifstream fs(file);
	std::string	file_content((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	std::string header("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:");
	header += std::to_string(file_content.length());
	std::string http_request = header + "\r\n\n" + file_content;

	return (http_request);
}


void    ServerConnexion::connexion_loop()
{
    std::string client_req;

    m_polling.init_epoll_events();
    while(1)
    {
        int nfds;
        nfds = m_polling.wait_for_connexions();// throw?

		for(int i = 0; i < nfds; i++) {
            struct epoll_event  event;

            event = m_polling.get_ready_event(i);
            // erreur dans la connexion client
            if ((event.events & EPOLLERR) ||
                (event.events & EPOLLHUP) ||
                (!(event.events & EPOLLIN))) {
                close (event.data.fd);
                continue;
            }
            // nouvelle connexion client
            else if (m_polling.is_existing_socket_fd(event.data.fd)) {
                int new_socket = m_polling.accept_connexion(event.data.fd);

                m_polling.set_socket(new_socket);
                m_polling.add_socket_to_epoll(new_socket);
                continue ;
            }
            // data dispo pour la lecture dans une connexion client
            else {
                bool    is_chunk = false;

                client_req = m_polling.receive_request(event.data.fd);
                if (m_chunks.is_chunk(event.data.fd, client_req)) {
                    is_chunk = true;
                    m_chunks.add_chunk(event.data.fd, client_req);
                    if (client_req[0] == '\0' || m_chunks.is_end_of_chunk(client_req)) {
                        client_req = m_chunks.get_unchunked_request(event.data.fd);
                        is_chunk = false;
                    }
                }
                if (!is_chunk) {
                    std::cout << "AAAAAAAAAAAAAAA\n" << client_req << std::endl;
                    // traitement de la requete ici
                    m_polling.send_request(create_response("unit_test/ConnexionTester/page.html"), event.data.fd);
			        close(event.data.fd);				
                }
            }
		}
    }
	m_polling.close_epfd();
}
