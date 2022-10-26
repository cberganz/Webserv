#ifndef CHUNKS_HPP
# define CHUNKS_HPP

# include <map>
# include <vector>
# include <algorithm>
# include <string>
# include <iostream>
# include <sstream>
# include <iostream>
# include "../tools/utility.hpp"

# define MAX_CHUNK_LEN  32768

class Chunks {
    private:
        std::map<int, std::vector<char> >                   m_chunked_requests;
        std::map<int, std::pair<int, std::vector<char> > >   m_chunked_responses;

        int             go_to_end_of_line(std::vector<char> &req, size_t i);
        bool            is_chunked_header(int fd);
        bool            findChunkedReq(int fd);

    public:
        Chunks();
        Chunks(const Chunks &copy);
        ~Chunks();
        Chunks &operator=(const Chunks &copy);

        /** REQUEST **/
        void                add_chunk_request(int fd, std::vector<char> chunk);
        std::vector<char>   get_unchunked_request(int fd);

        /** RESPONSE **/
        std::vector<char>     add_headerless_response_to_chunk(int fd, std::vector<char> response);
        std::vector<char>     get_next_response_chunk(int fd);

        /** UTILS **/
        bool            is_chunk_encoding(int fd);
        void            delete_chunk_request(int fd);
        void            delete_chunk_response(int fd);
        bool            body_is_whole(int fd);
        bool            boundary_reached(int fd, std::vector<char> chunk);
        void            increment_size_turn(int fd);
        int             get_size_return(int fd);
};

#endif