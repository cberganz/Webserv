#include "ClientRequest.hpp"

int	main()
{
	ClientRequest("\n\r\nGET /test%51 HTTP/1.1\nt:  test    \ntest2:23");
	return (0);
}
