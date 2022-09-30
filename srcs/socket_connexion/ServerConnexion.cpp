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
    m_polling.init_epoll_events();
    while(1)
    {
        int nfds;
        nfds = m_polling.wait_for_connexions();// throw?

		for(int i = 0; i < nfds; i++) {
            struct epoll_event  event;
			int                 new_socket;

            // Accept the connection
            event = m_polling.get_ready_event(i);
            new_socket = m_polling.accept_connexion(event.data.fd);
            m_polling.receive_request(new_socket);
            m_polling.send_request(create_response("unit_test/ConnexionTester/page.html"), new_socket);
			
			close(new_socket);				
		}
    }
	m_polling.close_epfd();
}
