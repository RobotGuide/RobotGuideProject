#include <iostream>
#include <string>

#include "SocketException.h"
#include "WindowsListener.h"
#include "WindowsConnection.h"
#include <vector>

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

	std::string str;
	std::vector<IConnection*> connections;

	while (true)
	{
		try
		{
			const int handle = listener.Accept();
			connections.push_back(new WindowsConnection(handle));
			std::cout << handle << std::endl;
		}
		catch (SocketException& e)
		{
			std::cout << e.what() << std::endl;
		}

		//Loop trough all active connections and send them the message. If it is not connected it will be removed from the list. (This is a temporary demo).
		try
		{
			auto iterator = connections.begin();
			while (iterator != connections.end())
			{
				if ((*iterator)->IsConnected())
				{
					(*iterator)->Send(str.c_str(), str.length());
					std::cout << "Sent: " << str << std::endl;
					++iterator;
				}
				else
				{
					iterator = connections.erase(iterator);
				}
			}
			std::cout << "There are: " << connections.size() << " connections" << std::endl;
			
		}
		catch (SocketException& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::getline(std::cin, str);
		std::cout << str << std::endl;
	}
}
