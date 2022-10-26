#include "ServerConnexion.hpp"

ServerConnexion::ServerConnexion() : m_config(), m_polling() {}

ServerConnexion::ServerConnexion(const std::string &path)
	: m_config(path),
	  m_polling(m_config.getGlobalContextsContainer()),
      m_rep_handler(m_config)
{}

ServerConnexion::ServerConnexion(const ServerConnexion &copy) {
    if (this != &copy)
        *this = copy;
}

ServerConnexion::~ServerConnexion() {}

ServerConnexion &ServerConnexion::operator=(const ServerConnexion &copy) {
    if (this != &copy)
        m_polling = copy.m_polling;
    return (*this);
}

std::vector<char>	ServerConnexion::createDefaultErrorPage(std::string file, 
															std::string status_code,
															std::string msg)
{
	std::ifstream       fs(file.c_str());
	std::string         file_content((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	std::string         header("HTTP/1.1 " + status_code + " " + msg
                                + "\nContent-Type: text/html\nTransfer-Encoding: chunked\nContent-Length:");
	header += ft::itostr(file_content.length());
	std::string         http_request = header + "\r\n\r\n" + file_content;

	return (std::vector<char>(http_request.begin(), http_request.end()));
}

std::string ServerConnexion::getSocketPort(int sockfd)
{
    t_sockaddr_in       addr;
    socklen_t           addrlen;

    memset((char *)&addr, 0, sizeof(addr));
    addrlen = sizeof(addr);
    getsockname(sockfd, (struct sockaddr *)&addr, &addrlen);
    return (ft::itostr(htons(addr.sin_port)));
}

std::string ServerConnexion::getSocketIp(int sockfd)
{
    uint32_t            ip_val;
    t_sockaddr_in       addr;
    socklen_t           addrlen;
    std::stringstream   ss;

    memset((char *)&addr, 0, sizeof(addr));
    addrlen = sizeof(addr);
    getsockname(sockfd, (struct sockaddr *)&addr, &addrlen);
    ip_val = htonl(addr.sin_addr.s_addr);
    for (int i = 0; i < 4; i++)
    {
        ss << (ip_val >> 8 * (3 - i) & 0xff);
        if (i != 3)
            ss << ".";
    }
    return (ss.str());
}

void    ServerConnexion::handleResponse(std::vector<char> client_req, int fd)
{
    m_rep_handler.setClientRequest(client_req);
    std::vector<char> response_msg
        = m_rep_handler.createResponseMessage(getSocketIp(fd), getSocketPort(fd));
    m_polling.send_response(m_chunks.add_headerless_response_to_chunk(fd,
        response_msg), fd);
}

void    ServerConnexion::handleDefaultError(ErrorException & e, int fd)
{
    HttpCodes           http_code;
    std::vector<char>   error_page = createDefaultErrorPage(e.getFile(), ft::itostr(e.getCode()), http_code[e.getCode()]);

    if (e.getFile() == "./app/error_pages/template.html"
        && (ft::search_vector_char(error_page, "$STATUS", 0) != -1
        || ft::search_vector_char(error_page, "$MESSAGE", 0) != -1))
    {
        error_page = ft::replace_vector_char(error_page, ft::search_vector_char(error_page, "$STATUS", 0),  7, ft::itostr(e.getCode()));
        error_page = ft::replace_vector_char(error_page, ft::search_vector_char(error_page, "$MESSAGE", 0),  8, http_code[e.getCode()]);
    }
    m_polling.send_response(m_chunks.add_headerless_response_to_chunk(fd, error_page), fd);
}

bool            ServerConnexion::is_last_request_chunk(std::vector<char> client_req, int fd) {
    if (client_req.size() < MAXBUF && ft::search_vector_char(client_req, "Transfer-Encoding: chunked", 0) == -1) {
        if (m_chunks.body_is_whole(fd) || m_chunks.boundary_reached(fd, client_req))
            return (true);
    }
    if (((ft::search_vector_char(client_req, "\r\n", 0) == 0 && client_req.size() == 2) 
        || ft::search_vector_char(client_req, "0\r\n", 0) != -1) && m_chunks.is_chunk_encoding(fd))
        return (true);
    return (false);
}

void    ServerConnexion::read_from_client(int fd) {
    try {
        bool                is_chunk    = true;
        std::vector<char>   client_req  = m_polling.receive_request(fd);

        if (!client_req.size())
            return ;
        m_chunks.add_chunk_request(fd, client_req);
        if (is_last_request_chunk(client_req, fd)) {
            is_chunk = false;
            client_req = m_chunks.get_unchunked_request(fd);
        }
        if (!is_chunk) {
            try {
                handleResponse(client_req, fd);
            } catch (ErrorException & e) {
                handleDefaultError(e, fd);
            }
            m_polling.edit_socket_in_epoll(fd, EPOLLOUT);
            m_chunks.delete_chunk_request(fd);
        }
    }
    catch (const std::exception& e) {
        close(fd);
        m_chunks.delete_chunk_request(fd);
		std::cerr << "Exception: "<< e.what() << '\n';
    }
}

void    ServerConnexion::write_to_client(int fd) {
    try {
        std::vector<char>   chunk = m_chunks.get_next_response_chunk(fd);
        int                 size_return = m_chunks.get_size_return(fd);
        std::vector<char>   response;
        std::stringstream   ss;
        std::string         size_chunk;

        ss << std::hex << chunk.size();
        ss >> size_chunk;
        if (size_return % 2 == 0)
            response.insert(response.end(), size_chunk.begin(), size_chunk.end());
        else
            response = chunk;
        response.push_back('\r');
        response.push_back('\n');
        m_polling.send_response(response, fd);
        if (!chunk.size() && size_return % 2 == 1) 
            m_polling.edit_socket_in_epoll(fd, EPOLLIN);
        if (!chunk.size() && size_return % 2 == 1){
            m_chunks.delete_chunk_response(fd);
            close (fd);
        }
        else
            m_chunks.increment_size_turn(fd);
    }
    catch (const std::exception& e) {
        close(fd);
        m_chunks.delete_chunk_response(fd);
		std::cerr << "Exception: "<< e.what() << '\n';
    }
}

void    ServerConnexion::connexion_loop()
{
    try {
        m_polling.init_epoll_events();
	    while(1)
        {
            int nfds;
            nfds = m_polling.wait_for_connexions();

            for(int i = 0; i < nfds; i++) {
                struct epoll_event  event;

                event = m_polling.get_ready_event(i);
                if ((event.events & EPOLLERR) || (event.events & EPOLLHUP)
                    || (event.events & EPOLLRDHUP)) {
                    m_chunks.delete_chunk_request(event.data.fd);
                    m_chunks.delete_chunk_response(event.data.fd);
                    close (event.data.fd);
                }
                else if (m_polling.is_existing_server_socket_fd(event.data.fd))
                    m_polling.new_client_connexion(event.data.fd);
                else if (event.events & EPOLLIN) 
                    read_from_client(event.data.fd);
                else if (event.events & EPOLLOUT)
                    write_to_client(event.data.fd);
            }
        }
    }
    catch(const std::exception& e) {
		std::cerr << "Exception: "<< e.what() << '\n';
	}
}
