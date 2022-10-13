int main(int argc, char const *argv[])
{
	std::vector<int>	ports;
	ports.push_back(PORT2);
	ports.push_back(PORT1);

	socket_connexion(ports);
    return 0;
}#include <stdio.h>
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

#define PORT1 8080
#define PORT2 8081
#define MAXBUF 3000


void	socket_connexion(std::vector<int> ports)
{
	std::ifstream fs("page.html");
	std::string	file_content((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	std::string header("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length:");
	header += std::to_string(file_content.length());
	std::string http_request = header + "\r\n\n" + file_content;


	char buffer[MAXBUF];
    std::vector<int> server_fd(ports.size());
	long valread;
	struct epoll_event events[ports.size()];
	int epfd = epoll_create(10);

    // Creating socket file descriptor


	for (size_t i = 0; i < ports.size(); i++)
	{
		struct sockaddr_in address;
		static struct epoll_event ev;
		
		if ((server_fd[i] = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
			perror("In socket");
			exit(EXIT_FAILURE);
		}
		
		int on = 1;

		if (setsockopt(server_fd[i], SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT,
										&on, sizeof(int)) < 0)
		{
				std::cerr << "error: setsockopt() failed" << std::endl;
				close(server_fd[i]);
				exit(1);
		}

		if(fcntl(server_fd[i], F_SETFL, O_NONBLOCK) < 0)
		{
			std::cerr << "could not set socket to be non blocking" << std::endl;
			exit(1);
		}
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons( ports[i] );
		
		memset(address.sin_zero, '\0', sizeof(address.sin_zero));
		
		
		if (bind(server_fd[i], (struct sockaddr *)&address, sizeof(address))<0)
		{
			perror("In bind");
			exit(EXIT_FAILURE);
		}
		if (listen(server_fd[i], 10) < 0)
		{
			perror("In listen");
			exit(EXIT_FAILURE);
		}

		memset(&address, 0, sizeof (address));
		int addrlen = sizeof(address);
		
		// ev.data.fd = server_fd[i];

		ev.data.fd = accept(server_fd[i],(struct sockaddr*)&address, (socklen_t*)&addrlen);
		ev.events = EPOLLIN;
		epoll_ctl(epfd, EPOLL_CTL_ADD, ev.data.fd, &ev);
	}

    while(1)
    {
		puts("round again");
		int nfds = epoll_wait(epfd, events, ports.size(), 10000);
		
		for(int i=0; i<nfds; i++) {
				memset(buffer,0,MAXBUF);
				read(events[i].data.fd, buffer, MAXBUF);
				
