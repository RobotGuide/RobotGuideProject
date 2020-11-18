#include <iostream>
#include  "WindowsListener.h"
#include "SocketException.h"

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

	WindowsListener listener(nullptr, "3030", &hints);
	listener.Listen(10);
	std::cout << "Started" << std::endl;

	while (true)
	{
		try
		{
			const int handle = listener.Accept();
			std::cout << handle << "Connected" << std::endl;
			break;
		}
		catch (SocketException& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cin.get();
}
