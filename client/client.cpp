#include "client.h"

client::client(std::string name)
{
	userName = name;
}


bool client::setupClient()
{
	//WSA Startup
	if (WSAStartup((2, 2), &wsaData) != 0)
	{
		std::cout << "WSAStartup Failed" << std::endl;
		return 0;
	}

	sockFD = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFD == INVALID_SOCKET)
	{
		std::cout << "socket failed!" << std::endl;
		return 0;
	}

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(PORT);
	clientAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

	if (connect(sockFD, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
	{
		std::cout << "connect failed!" << std::endl;
		return 0;
	}
	int sender = send(sockFD, userName.c_str(), userName.length(), 0);
	return 1;
}

void client::closeClient()
{
	shutdown(sockFD, SD_BOTH);
	closesocket(sockFD);
	WSACleanup();
}

int client::sendData(std::string data)
{
	int sender = send(sockFD, data.c_str(), data.length(), 0);
	return sender;
}

char* client::receiveData()
{
	memset(buffer, 0, SERVER_BUF);
	int rec = recv(sockFD, buffer, SERVER_BUF, 0);
	return buffer;
}

