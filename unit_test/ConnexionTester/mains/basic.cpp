#include "../../../srcs/socket_connexion/ServerConnexion.hpp"

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments count !" << std::endl;
		return 1;
	}
	try
	{
		ServerConnexion server(argv[1]);
		server.connexion_loop();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: "<< e.what() << '\n';
	}

    return 0;
}
