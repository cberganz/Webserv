#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sys/epoll.h>  
#include <fcntl.h>
#include <errno.h>

#define PORT1 8080
#define PORT2 8081
#define MAXBUF 3000
#define MAX_EVENTS 5

int    create_socket(int port)
{
    int    len, rc, on = 1;
    int    listen_sd = -1, new_sd = -1;
	struct sockaddr_in serv_addr;

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sd < 0)
    {
        perror("socket() failed");
        exit(-1);
    }

    rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, 
                    &on, sizeof(int));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }

    if(fcntl(listen_sd, F_SETFL, O_NONBLOCK) < 0)
    {
        std::cerr << "could not set socket to be non blocking" << std::endl;
        exit(1);
    }

	memset(serv_addr.sin_zero, '\0', sizeof(serv_addr.sin_zero));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons( port );
		
	rc = bind(listen_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }

    rc = listen(listen_sd, 100);
    if (rc < 0)
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }
    return (listen_sd);
}

std::string	create_response(std::string file) {
	std::ifstream fs(file);
	std::string	file_content((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	std::string header("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:");
	header += std::to_string(file_content.length());
	std::string http_request = header + "\r\n\n" + file_content;

	return (http_request);
}

void	socket_connexion(std::vector<int> ports)
{
	std::string http_request = create_response("page.html");

	char buffer[MAXBUF];
    std::vector<int> server_fd;

	struct epoll_event ready_events[MAX_EVENTS];
	int epfd = epoll_create(10);
    if (epfd < 0) {
        std::cout << "Failed epoll_create.\n";
        return ;
    }

	for (size_t i = 0; i < ports.size(); i++)
	{
		struct epoll_event conf_event;

		server_fd.push_back(create_socket(ports[i]));
		conf_event.events = EPOLLIN;
		conf_event.data.fd = server_fd[i];
		epoll_ctl(epfd, EPOLL_CTL_ADD, conf_event.data.fd, &conf_event);
	}

    while(1)
    {
		
        std::cout << "\rPolling for input: " << std::flush;
		int nfds = epoll_wait(epfd, ready_events, MAX_EVENTS, 5000);		
		if (nfds == -1) {
			std::cout << strerror(errno) << " " << errno << std::endl;
			return ;
		}

		for(int i=0; i<nfds; i++) {
			std::cout << "\r" << "Client connected on server: " << ready_events[i].data.fd << std::endl;

			// Accept the connection
			int new_socket;
			if ((new_socket = accept(ready_events[i].data.fd, NULL, NULL)) < 0)
			{
				std::cerr << "error: accept() failed" << std::endl;
				close(new_socket);
				exit(1);
			}

			// receive
			int ret = 0;
			if ((ret = recv(new_socket, &buffer, 1023, 0)) < 0)
			{
				std::cerr << "error: recv() failed" << std::endl;
				exit(1);
			}
			buffer[ret] = '\0';
			std::cout << buffer << std::endl;

			// send
			if((ret = send(new_socket, http_request.c_str(), http_request.length(), 0)) < 0) {
				std::cerr << "error: send() failed" << std::endl;
				exit(1);
			}
			close(new_socket);				
		}
    }
	close(epfd);
}

int main(int argc, char const *argv[])
{
	std::vector<int>	ports;
	ports.push_back(PORT2);
	ports.push_back(PORT1);

	socket_connexion(ports);
    return 0;
}