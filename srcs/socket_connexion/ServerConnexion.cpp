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
	std::string header("HTTP/1.1 200 OK\nContent-Type: text/html\nTransfer-Encoding: chunked\nContent-Length:");
	header += std::to_string(file_content.length());
	std::string http_request = header + "\r\n\r\n" + file_content;

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
                (!(event.events & EPOLLIN) && !(event.events & EPOLLOUT))) {
                close (event.data.fd);
                continue;
            }
            // nouvelle connexion client
            else if (m_polling.is_existing_socket_fd(event.data.fd)) {
                m_polling.new_client_connexion(event.data.fd);
                continue ;
            }
            // data dispo pour la lecture dans une connexion client
            else if (event.events & EPOLLIN) {
                bool    is_chunk = false;

                client_req = m_polling.receive_request(event.data.fd);
                if (m_chunks.is_chunk(event.data.fd, client_req)) {
                    is_chunk = true;
                    if (!m_chunks.is_chunked_header(event.data.fd)) {
                        client_req = m_polling.receive_request(event.data.fd);
                    }
                    m_chunks.add_chunk_request(event.data.fd, client_req);
                    if (client_req.find("0\r\n") != std::string::npos) {
                        client_req = m_chunks.get_unchunked_request(event.data.fd);
                        is_chunk = false;
                    }
                }
                if (!is_chunk) {
                    // traitement de la requete ici
                    std::string header = m_chunks.add_headerless_response_to_chunk(event.data.fd,
                        create_response("unit_test/ConnexionTester/page.html"));
                    m_polling.send_request(header, event.data.fd);
                    m_polling.edit_socket_in_epoll(event.data.fd, EPOLLOUT);
                }
            }
            // socket client dispo pour l'ecriture
            else if (event.events & EPOLLOUT) {
                std::string chunk = m_chunks.get_next_chunk(event.data.fd);

                std::stringstream   ss;
                std::string         size_chunk; 
                ss << std::hex << chunk.size();
                ss >> size_chunk;

                m_polling.send_request(size_chunk + "\r\n", event.data.fd);
                m_polling.send_request(chunk + "\r\n", event.data.fd);
                if (chunk == "") 
                    m_polling.edit_socket_in_epoll(event.data.fd, EPOLLIN);
            }
		}
    }
	m_polling.close_epfd();
}
