#ifndef CHUNKED_REQUESTS_HPP
# define CHUNKED_REQUESTS_HPP

# include <map>
# include <string>
# include <iostream>

class ChunkedRequests {
    private:
        std::map<int, std::string>  m_chunked_requests;

    public:
        ChunkedRequests();
        ChunkedRequests(const ChunkedRequests &copy);
        ~ChunkedRequests();
        ChunkedRequests &operator=(const ChunkedRequests &copy);

        void            add_chunk(int fd, std::string chunk);
        std::string     get_unchunked_request(int fd);
        bool            is_chunk(int fd, std::string chunk);
        bool            is_end_of_chunk(std::string chunk);
};

#endif