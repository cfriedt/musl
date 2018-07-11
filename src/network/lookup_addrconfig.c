#include "lookup.h"

#include <sys/types.h>
#include <ifaddrs.h>
#include <netdb.h>
#define _BSD_SOURCE
#include <net/if.h>

int __lookup_addrconfig( struct addrconfig *cfg ) {
	int r;
	struct ifaddrs *ifap;
	struct ifaddrs *it;

	r = getifaddrs(&ifap);
	if ( 0 != r ) {
		return EAI_SYSTEM;
	}

	for(
		cfg->af_inet = false, cfg->af_inet6 = false, it = ifap;
		!( NULL == it || ( cfg->af_inet && cfg->af_inet6 ) );
		it = it->ifa_next
	) {
		switch(it->ifa_addr->sa_family) {
		case AF_INET:
			cfg->af_inet = true;
			break;
		case AF_INET6:
			cfg->af_inet6 = true;
			break;
		default:
			continue;
		}
	}

	freeifaddrs( ifap );

	return 0;
}
