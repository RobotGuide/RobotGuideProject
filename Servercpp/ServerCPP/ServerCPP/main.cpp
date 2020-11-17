#include <iostream>
#include  "WindowsListener.h"
#include "SocketException.h"

int main()
{
	std::cout << "Boot Up" << std::endl;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	
	addrinfo hints{};
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	try
	{
		WindowsListener listener(nullptr, "3030", &hints);
		listener.Listen(10);
		std::cout << "Started" << std::endl;
	}
	catch (SocketException& exception)
	{
		std::cout << exception.what() << std::endl;
	}

	while (true)
	{

	}
}
