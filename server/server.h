#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <map>

#pragma comment (lib, "ws2_32.lib")

#define DEFAULT_PORT    61061
#define SERVER_BUF      50

class server 
{
public:
	server();
	void setupServer();
	int getSocketCount();
	void connect();
	void closeServer();
	void whoseMessage(std::string message, std::string& rec, std::string& dat);
	void sendMessage(SOCKET sock);

private:
	WSADATA wsaData;
	SOCKET listenSocket;
	struct sockaddr_in serverAddr;
	fd_set clients, temp;
	int socketCount;
	char buffer[SERVER_BUF], clientName[SERVER_BUF];
	std::map<std::string, int> clientList;
	const std::string seperator = "'dan mesaj: ";
};


#endif