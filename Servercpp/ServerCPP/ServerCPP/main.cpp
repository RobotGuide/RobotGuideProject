#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/WindowsListener.h"
#include <iostream>


//Required for windows socket
#pragma comment(lib, "Ws2_32.lib")
#undef  UNICODE

using namespace robotguide::com::transportlayer;

int main()
{
	std::cout << "Boot Up" << std::endl;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	WindowsListener listener("127.0.0.1", "3030", hints);
	listener.Listen(10);
	return 1;
}
