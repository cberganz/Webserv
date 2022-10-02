#ifndef CHUNKS_HPP
# define CHUNKS_HPP

# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include <iostream>

# define MAX_CHUNK_LEN  20

class Chunks {
    private:
        std::map<int, std::string>  m_chunked_requests;
        std::map<int, std::string>  m_chunked_responses;

    public:
        Chunks();
        Chunks(const Chunks &copy);
        ~Chunks();
        Chunks &operator=(const Chunks &copy);

        /** REQUEST **/
        void            add_chunk_request(int fd, std::string chunk);
        std::string     get_unchunked_request(int fd);

        /** RESPONSE **/
        std::string     add_headerless_response_to_chunk(int fd, std::string response);
        std::string     get_next_chunk(int fd);

        /** UTILS **/
        bool            is_chunk(int fd, std::string chunk);
        bool            is_end_of_chunk(std::string chunk);
};

#endif