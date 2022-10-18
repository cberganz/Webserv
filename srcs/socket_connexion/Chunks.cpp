#include "Chunks.hpp"

/** COPLIEN **/

Chunks::Chunks( void ) {}

Chunks::Chunks(const Chunks &copy) {
    if (this != &copy)
        *this = copy;
}

Chunks::~Chunks() {}

Chunks &Chunks::operator=(const Chunks &copy) {
    if (this != &copy) {
        m_chunked_requests = copy.m_chunked_requests;
        m_chunked_responses = copy.m_chunked_responses;
    }
    return (*this);
}

/** CHUNKED REQUEST FUNCTIONS **/

void    Chunks::add_chunk_request(int fd, std::pair<int, std::vector<char> > chunk) {
    std::map<int, std::vector<char> >::iterator it = m_chunked_requests.find(fd);

    if (is_chunked_header(fd))
        m_chunked_requests.insert(std::make_pair(fd, chunk.second));
    else {
        if (is_chunk_encoding(fd))
            it->second.insert(it->second.end(), chunk.second.begin(), chunk.second.begin() + chunk.first - 2);
        else
            it->second.insert(it->second.end(), chunk.second.begin(), chunk.second.begin() + chunk.first);
    }
}

int Chunks::go_to_end_of_line(std::vector<char> req, int i) {
    while (i + 1 < req.size() && req[i] == '\r' && req[i + 1] == '\n')
        i += 2;
    return (i);
}

std::vector<char>     Chunks::get_unchunked_request(int fd) {
    std::vector<char>   req = m_chunked_requests.find(fd)->second;
    int                 i = ft::search_vector_char(req, "\r\n\r\n", 0);

    if (ft::search_vector_char_until(req, "Transfer-Encoding: chunked", i) == -1)
        return (req);
    i += 4;
    int j = ft::search_vector_char(req, "\r\n", i) + 2;
    
    while (j != 1) {
        req.erase(req.begin() + i, req.begin() + j);
        i = go_to_end_of_line(req, ft::search_vector_char(req, "\r\n", i));
        j = ft::search_vector_char(req, "\r\n", i) + 2;
    }
    return (req);
}

/** CHUNK RESPONSE FUNCTIONS **/

// returns header which will be sent first straight after receipt of request
std::string     Chunks::add_headerless_response_to_chunk(int fd, std::string response) {
    size_t        end_header = response.find("\r\n\r\n");
    std::string   header = response.substr(0, end_header + 4);

    m_chunked_responses.insert(std::make_pair(fd, std::make_pair(2, response.substr(end_header + 4))));
    return (header);
}

std::string     Chunks::get_next_chunk(int fd) {
    std::string response = (m_chunked_responses.find(fd))->second.second;
    int         size_turn = (m_chunked_responses.find(fd))->second.first;
    std::string chunk = "";
    
    if (response.size())
        chunk = response.substr(0, MAX_CHUNK_LEN);
    // if (size_turn % 2 == 0)
    //     return (chunk);
    if (response.size() >= MAX_CHUNK_LEN)
        response = response.substr(MAX_CHUNK_LEN); 
    else
        response = "";
    m_chunked_responses.erase(fd);
    if (chunk.size())
        m_chunked_responses.insert(std::make_pair(fd, std::make_pair(size_turn, response)));
    return (chunk);
}

/** UTILS **/

bool    Chunks::body_is_whole(int fd) {
    if (!findChunkedReq(fd))
        return (false);
    std::vector<char> req = m_chunked_requests.find(fd)->second;
    std::string content_length = "Content-Length: ";
    std::string saut_ligne = "\r\n\r\n";
    size_t size_begin = ft::search_vector_char(req, content_length.c_str(), 0) + 16;
    if (size_begin == 15)
        return (true);
    size_t size_end = ft::search_vector_char(req, saut_ligne.c_str(), size_begin);
    std::string size_str(req.begin() + size_begin, req.begin() + size_end);
    size_t  size = ft::lexical_cast<size_t>(size_str);
    size_t  size_body = 0;
    for (std::vector<char>::iterator it = req.begin() + ft::search_vector_char(req, "\r\n\r\n", 0) + 4; it != req.end(); it++)
        size_body++;

    if (size_body >= size)
        return (true);
    return (false);
}

bool            Chunks::is_chunked_header(int fd) {
    if (m_chunked_requests.find(fd) == m_chunked_requests.end())
        return (true);
    return (false);
}

bool            Chunks::findChunkedReq(int fd) {
    if (m_chunked_requests.find(fd) != m_chunked_requests.end())
        return (true);
    return (false);
}

bool            Chunks::is_chunk_encoding(int fd) {
    if (!findChunkedReq(fd))
        return (false);
    if (ft::search_vector_char(m_chunked_requests.find(fd)->second, "Transfer-Encoding: chunked", 0) != -1)
        return (true);
    return (false);
}

void            Chunks::delete_chunk_request(int fd) {
    m_chunked_requests.erase(fd);
}

void            Chunks::delete_chunk_response(int fd) {
    m_chunked_responses.erase(fd);
}

bool            Chunks::boundary_reached(int fd, std::vector<char> chunk) {
    std::vector<char> req = m_chunked_requests.find(fd)->second;
    size_t  boundary_position = ft::search_vector_char_until(req, "boundary=", ft::search_vector_char(req, "\r\n\r\n", 0));
    if (boundary_position == -1)
        return (true);
    std::string saut_ligne = "\r\n";
    std::string boundary(req.begin() + boundary_position + 9, std::search(req.begin() + boundary_position, req.end(), saut_ligne.begin(), saut_ligne.end()));
    boundary = "--" + boundary + "--";
    if (ft::search_vector_char(chunk, boundary.c_str(), 0) == -1)
        return (false);
    return (true);
}

void            Chunks::increment_size_turn(int fd) {
    m_chunked_responses.find(fd)->second.first++;
}

int             Chunks::get_size_return(int fd) {
    return (m_chunked_responses.find(fd)->second.first);
}