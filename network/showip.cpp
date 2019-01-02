#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <iostream>

// Displays the IP address of the hostname provided through standard input.
// Adapted for C++ from Beej Jorgenson's Guide to Network Programming 

int main(int argc, char const *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	//Check for Arguments
    if(argc != 2){
        std::cout << "Invalid number of arguments.\n" 
                  << "Usage: showip hostname\n";
        return 1;
    }

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
	{
		std::cerr << "IP addresses for " << gai_strerror(status) << "\n";
		return 2;
	}

	std::cout << "IP addresses for " << argv[1] << "\n\n";

	for(p = res; p != NULL; p = p->ai_next){
		void *addr;
		std::string ipver;
 		// get the pointer to the address itself,
 		// different fields in IPv4 and IPv6:
 		if (p->ai_family == AF_INET) { // IPv4
 			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
 			ipver = "IPv4";
		} else { // IPv6
 			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
 			addr = &(ipv6->sin6_addr);
 			ipver = "IPv6";
 		}
 		// convert the IP to a string and print it:
 		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
 		std::cout << " " << ipver << ": " << ipstr << "\n";
 	}
 	freeaddrinfo(res); // free the linked list
	return 0;
}