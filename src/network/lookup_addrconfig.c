#include "lookup.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void __lookup_addrconfig( struct addrconfig *cfg ) {
	int r;
	int fd;

	struct sockaddr_in sai = {
		.sin_family = AF_INET,
		.sin_port = htons( 42 ),
		.sin_addr.s_addr = INADDR_LOOPBACK,
	};
	cfg->af_inet = false;
	r = socket( AF_INET, SOCK_DGRAM, 0 );
	if ( -1 != r ) {
		fd = r;
		r = connect( fd, (struct sockaddr *) & sai, sizeof( sai ) );
		cfg->af_inet = 0 == r;
		close( fd );
	}

	struct sockaddr_in6 sai6 = {
		.sin6_family = AF_INET6,
		.sin6_port = htons( 42 ),
		.sin6_addr = IN6ADDR_LOOPBACK_INIT,
	};
	cfg->af_inet6 = false;
	r = socket( AF_INET6, SOCK_DGRAM, 0 );
	if ( -1 != r ) {
		fd = r;
		r = connect( fd, (struct sockaddr *) & sai6, sizeof( sai6 ) );
		cfg->af_inet6 = 0 == r;
		close( fd );
	}
}
