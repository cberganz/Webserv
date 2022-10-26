#include "../../srcs/response/ResponseMaker.hpp"
#include "../../srcs/client_request/ClientRequestParser.hpp"
#include <iostream>

std::string request = "GET / HTTP/1.1\r\nhost: localhost:8080\r\nconnection: keep-alive\r\ncache-control: max-age=0\r\nsec-ch-ua: \"Google Chrome\";v=\"105\", \"Not)A;Brand\";v=\"8\", \"Chromium\";v=\"105\"\r\nsec-ch-ua-mobile: ?0\r\nsec-ch-ua-platform: \"Linux\"\r\nupgrade-insecure-requests: 1\r\nuser-agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36\r\naccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\nsec-fetch-site: none\r\nsec-fetch-mode: navigate\r\nsec-fetch-user: ?1\r\nsec-fetch-dest: document\r\naccept-encoding: gzip, deflate, br\r\naccept-language: fr-FR,fr;q=0.9\r\n\r\n";

std::vector<char> strToVector(std::string)
{
	std::vector<char> v;
	for (std::string::size_type i = 0 ; i != request.size() ; i++)
		v.push_back(request[i]);
	return v;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments. Usage: ./a.out [configuration file path]" << std::endl;
		return 1;
	}
	ClientRequestParser parser;
	parser.setRequest(strToVector(request));
	Config config(argv[1]);
	ResponseMaker responseMaker(config);
	Context context = config.getServer("127.0.0.1", "8080");
	try {
		ClientRequest client_req = parser.makeClientRequest();
		Response response = responseMaker.createResponse(client_req, context, "/");
		std::vector<char> to_print = response.getResponse();
		for (std::vector<char>::iterator it = to_print.begin() ; it != to_print.end() ; it++)
			std::cout << *it;
		std::cout << std::endl;
	} catch (const ErrorException &e) {
		std::cout << e.getCode() << std::endl; 
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl; 
	}
	return 0;
}
