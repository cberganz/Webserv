#include "ChunkedRequests.hpp"
#include "ServerConnexion.hpp"


int main() {
	std::string	    request("HTTP/1.1 200 OK\r\nContent-Type: text//plain\r\nTransfer-Encoding: chunked\r\n\r\n26\r\nVoici les données du premier morceau\r\n\r\n10\r\net voici un second morceau\r\n\r\n20\r\net voici deux derniers morceaux \r\n12\r\nsans saut de ligne\r\n0\r\n\r\n");
    ChunkedRequests   chunk;

    chunk.add_chunk(1, request);
    std::cout << chunk.get_unchunked_request(1) << std::endl;
    return (0);
}