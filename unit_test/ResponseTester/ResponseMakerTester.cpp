#include "../../srcs/response/ResponseMaker.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments. Usage: ./a.out [configuration file path]" << std::endl;
		return 1;
	}
	Config config(argv[1]);
	ResponseMaker responseMaker(config);
	try {
		std::cout << (*responseMaker.createResponse("/", "127.0.0.1", "8080")).getResponse() << std::endl;
	} catch (const ErrorException &e) {
		std::cout << e.getCode() << std::endl; 
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl; 
	}
	return 0;
}
