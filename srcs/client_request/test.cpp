#include "ClientRequest.hpp"

int	main()
{
	ClientRequest("GET / HTTP/1.1\nHost: localhost:8080\nConnection: keep-alive\nCache-Control: max-age=0\nsec-ch-ua: 'Google Chrome';v='105', 'Not)A;Brand';v='8', 'Chromium';v='105'\nsec-ch-ua-mobile: ?0\nsec-ch-ua-platform: 'Linux'\nUpgrade-Insecure-Requests: 1\nSec-Fetch-Site: none\nSec-Fetch-Mode: navigate\nSec-Fetch-User: ?1\nSec-Fetch-Dest: document\nAccept-Language: fr-FR,fr;q=0.9\nAccept-Encoding: gzip, deflate, br\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/105.0.0.0 Safari/537.36\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\nsec-ch-ua:  'Google Chrome';v='105', 'Not)A;Brand';v='8', 'Chromium';v='105'\n\n{moi: je teste le body}");
	return (0);
}