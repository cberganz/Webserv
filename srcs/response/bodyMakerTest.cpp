#include "BodyMaker.hpp"
#include <iostream>

int main()
{
	BodyMaker body;
	try {
		std::cout << body.createBody("test.php") << std::endl;
		//body.createBody("test.php");
	} catch (ErrorException &e) {
		std::cout << e.getCode() << std::endl; 
	}
	return 0;
}
