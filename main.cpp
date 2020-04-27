#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <sys/types.h>
#include <iostream>
#include <sstream>

#include <linux/libc-compat.h>

int main()
{

	ifaddrs* interfaces_list = nullptr;
	getifaddrs(&interfaces_list);

	for(ifaddrs* i= interfaces_list; i != nullptr; i= i->ifa_next)
	{
		if(i->ifa_addr == nullptr)
			continue;

		const char* family= "unknoqwn";
		if(i->ifa_addr->sa_family == AF_INET)
			family= "AF_INET";
		if(i->ifa_addr->sa_family == AF_INET6)
			family= "AF_INET6";
		if(i->ifa_addr->sa_family == AF_UNIX)
			family= "AF_UNIX";
		if(i->ifa_addr->sa_family == AF_X25)
			family= "AF_X25";
		if(i->ifa_addr->sa_family == AF_LOCAL)
			family= "AF_LOCAL";
		if(i->ifa_addr->sa_family == AF_PACKET)
			family= "AF_PACKET";

		std::string addr_str;
		if(i->ifa_addr->sa_family == AF_INET)
		{
			const auto addr_ipv4= reinterpret_cast<const struct sockaddr_in*>(i->ifa_addr);
			const uint32_t addr = addr_ipv4->sin_addr.s_addr;
			addr_str=
				std::to_string(addr & 255) + "." +
				std::to_string((addr >>  8) & 255) + "." +
				std::to_string((addr >> 16) & 255) + "." +
				std::to_string((addr >> 24) & 255);
		}
		if(i->ifa_addr->sa_family == AF_PACKET)
		{
			const auto addr_mac= reinterpret_cast<const struct sockaddr_ll*>(i->ifa_addr);

			std::stringstream ss;

			for(int i = 0; i < addr_mac->sll_halen; ++i)
				ss << std::hex << int(addr_mac->sll_addr[i]) << ":";
			addr_str = ss.str();
		}

		std::string flags;
		if((i->ifa_flags & IFF_UP) != 0)
			flags += "IFF_UP ";
		if((i->ifa_flags & IFF_BROADCAST) != 0)
			flags += "IFF_BROADCAST ";
		if((i->ifa_flags & IFF_LOOPBACK) != 0)
			flags += "IFF_LOOPBACK ";
		if((i->ifa_flags & IFF_AUTOMEDIA) != 0)
			flags += "IFF_AUTOMEDIA ";
		if((i->ifa_flags & IFF_PORTSEL) != 0)
			flags += "IFF_PORTSEL ";
		if((i->ifa_flags & IFF_MULTICAST) != 0)
			flags += "IFF_MULTICAST ";
		if((i->ifa_flags & IFF_DYNAMIC) != 0)
			flags += "IFF_DYNAMIC ";
		if((i->ifa_flags & IFF_NOARP) != 0)
			flags += "IFF_NOARP ";

		std::cout << "Interface: " << i->ifa_name << ", family: " << family << ", address: " << addr_str << ", flags: " << flags << " (" << std::hex << "0x" << i->ifa_flags << ")" << std::endl;
	}

	freeifaddrs(interfaces_list);
}
