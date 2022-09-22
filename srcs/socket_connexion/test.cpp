#include "ServerConnexion.hpp"

#define PORT1 8080
#define PORT2 8081

int main(int argc, char const *argv[])
{
	std::vector<int>	ports;
	ports.push_back(PORT2);
	ports.push_back(PORT1);

	ServerConnexion server(ports);

	server.connexion_loop();
    return 0;
}