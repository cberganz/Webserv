#include "ChunkedRequests.hpp"

/** COPLIEN **/

ChunkedRequests::ChunkedRequests( void ) {}

ChunkedRequests::ChunkedRequests(const ChunkedRequests &copy) {
    if (this != &copy)
        *this = copy;
}

ChunkedRequests::~ChunkedRequests() {}

ChunkedRequests &ChunkedRequests::operator=(const ChunkedRequests &copy) {
    if (this != &copy)
        m_chunked_requests = copy.m_chunked_requests;
    return (*this);
}

/** CHUNK FUNCTIONS **/

void    ChunkedRequests::add_chunk(int fd, std::string chunk) {
    std::map<int, std::string>::iterator it = m_chunked_requests.find(fd);

    if (it == m_chunked_requests.end())
        m_chunked_requests.insert(std::make_pair(fd, chunk));
    else 
        it->second += chunk;
}

std::string     ChunkedRequests::get_unchunked_request(int fd) {
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

bool            ChunkedRequests::is_chunk(int fd, std::string chunk) {
    if (m_chunked_requests.find(fd) != m_chunked_requests.end())
        return (true);
    if (chunk.find("Transfer-Encoding: chunked") != std::string::npos)
        return (true);
    return (false);
}

bool            ChunkedRequests::is_end_of_chunk(std::string chunk) {
    if (chunk.find("0\r\n\r\n") != std::string::npos)
        return (true);
    return (false);
}
