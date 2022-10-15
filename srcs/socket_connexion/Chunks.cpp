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

void    Chunks::add_chunk_request(int fd, std::vector<char> chunk) {
    std::map<int, std::vector<char> >::iterator it = m_chunked_requests.find(fd);

    if (is_chunked_header(fd))
        m_chunked_requests.insert(std::make_pair(fd, chunk));
    else 
        it->second.insert(it->second.end(), chunk.begin(), chunk.end() - 2);
}

std::vector<char>     Chunks::get_unchunked_request(int fd) {
    return (m_chunked_requests.find(fd)->second);
}

/** CHUNK RESPONSE FUNCTIONS **/

// returns header which will be sent first straight after receipt of request
std::string     Chunks::add_headerless_response_to_chunk(int fd, std::string response) {
    size_t        end_header = response.find("\r\n\r\n");
    std::string   header = response.substr(0, end_header + 4);

    m_chunked_responses.insert(std::make_pair(fd, response.substr(end_header + 4)));
    return (header);
}

std::string     Chunks::get_next_chunk(int fd) {
    std::string response = (m_chunked_responses.find(fd))->second;
    std::string chunk = "";
    
    if (response.size())
        chunk = response.substr(0, MAX_CHUNK_LEN);
    if (response.size() >= MAX_CHUNK_LEN)
        response = response.substr(MAX_CHUNK_LEN); 
    else
        response = "";
    m_chunked_responses.erase(fd);
    if (chunk.size())
        m_chunked_responses.insert(std::make_pair(fd, response));
    return (chunk);
}

/** UTILS **/

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

