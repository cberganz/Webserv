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

void    Chunks::add_chunk_request(int fd, std::string chunk) {
    std::map<int, std::string>::iterator it = m_chunked_requests.find(fd);

    if (it == m_chunked_requests.end())
        m_chunked_requests.insert(std::make_pair(fd, chunk));
    else 
        it->second += chunk;
}

std::string     Chunks::get_unchunked_request(int fd) {
    std::string request = m_chunked_requests.find(fd)->second;
    size_t      find_i = 0;
    bool        first = true;

    for (size_t i = 0; i < request.size(); i++) {
        if ((find_i = request.find("\r\n", i)) != std::string::npos) {
            i = find_i + 2;
            if (!isdigit(request[i])) {
                i--;
                continue ;
            }
            while (isdigit(request[i]))
                i++;
            if (request.find("\r\n", i) != i)
                continue ;
            if (first) {
                first = false;
                request.erase(find_i, i - find_i);
            }
            else
                request.erase(find_i, i + 2 - find_i);
            i -= (i + 2 - find_i);
        }
    }
    request.erase(request.size() - 2, 2);
    m_chunked_requests.erase(fd);
    return (request);
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
bool            Chunks::is_chunk(int fd, std::string chunk) {
    if (m_chunked_requests.find(fd) != m_chunked_requests.end())
        return (true);
    if (chunk.find("Transfer-Encoding: chunked") != std::string::npos)
        return (true);
    return (false);
}

bool            Chunks::is_end_of_chunk(std::string chunk) {
    if (chunk.find("0\r\n\r\n") != std::string::npos)
        return (true);
    return (false);
}
