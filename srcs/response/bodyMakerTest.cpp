#include "ResponseMaker.hpp"
#include <iostream>

int main()
{
	Config config("default.conf");
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
