#ifndef CLIENT_H
#define CLIENT_H

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <WinSock2.h>
#include <cstdio>

#pragma comment(lib, "Ws2_32.lib")

#define		PORT			61061
#define		SERVER_IP		"192.168.1.40"
#define		SERVER_BUF      50

class client {
public:
	client(std::string name);
	bool setupClient();
	void closeClient();
	int sendData(std::string data);
	char* receiveData();

private:

	WSADATA wsaData;
	SOCKET sockFD;
	std::string userName;
	struct sockaddr_in clientAddr;
	char buffer[SERVER_BUF];

};


#endif