#include "socket_connexion/ServerConnexion.hpp"

int main(int argc, char const *argv[])
{
	std::string path;
	if (argc > 2)
	{
		std::cerr << "Usage: ./webserv [path to configuration file]" << std::endl;
		return 0;
	}
	if (argc == 2)
	{
		path = argv[1];
		if (path.find_last_of(".") == std::string::npos || path.substr(path.find_last_of("."), path.size()) != ".conf"
			|| path.size() <= 5)
		{
			std::cerr << "Usage: ./webserv [path to configuration file]" << std::endl;
			return 0;
		}
	}
	if (argc == 1)
		path = "config_files/default.conf";
	try {
		ServerConnexion server(path);
	
		server.connexion_loop();
	}
	catch (const std::exception &e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
    return 0;
}
