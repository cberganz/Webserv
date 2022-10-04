#include "ClientRequest.hpp"
#include "ClientRequestParser.hpp"

int	main()
{
	ClientRequest		*req;
	ClientRequestParser test("\n\r\nGET /test%51 HTTP/1.1\nt:  test    \ntest2:23");

	req = test.makeClientRequest();
	req->print();
	return (0);
}
