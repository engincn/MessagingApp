#include "server.h"

server::server()
{
}

void server::setupServer()
{
    //WSA Startup
    if (WSAStartup((2, 2), &wsaData) != 0)
    {
        std::cout << "WSAStartup Failed" << std::endl;
    }
    //Socket create
    (listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
    if (listenSocket == INVALID_SOCKET)
    {
        std::cout << "socket failed!" << std::endl;
    }
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(DEFAULT_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //Bind
    if ((bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == SOCKET_ERROR)
    {
        std::cout << "Bind failed!" << std::endl;
    }
    //Listening
    if (listen(listenSocket, 3) == SOCKET_ERROR)
    {
        std::cout << "listen failed!" << std::endl;
    }

    FD_ZERO(&clients);
    FD_SET(listenSocket, &clients);

}

int server::getSocketCount()
{
    temp = clients;
    socketCount = select(0, &temp, nullptr, nullptr, nullptr);
    return socketCount;
}

void server::connect()
{
    
    getSocketCount();

    for (int i = 0; i < socketCount; i++)
    {
        SOCKET sock = temp.fd_array[i];
        if (sock == listenSocket)
        {
            SOCKET client = accept(listenSocket, nullptr, nullptr);
            int recName = recv(client, clientName, SERVER_BUF, 0);
            if (recName > 0)
            {
                std::string name(clientName);
                clientList[name] = client;
            }
            else
            {
                std::cout << "could not get name" << std::endl;
            }
            
            FD_SET(client, &clients);
        }
        else
        {
            sendMessage(sock);
        }
    }
}

void server::closeServer()
{
    FD_CLR(listenSocket, &clients);
    shutdown(listenSocket, SD_BOTH);
    closesocket(listenSocket);
    WSACleanup();
}

void server::whoseMessage(std::string message, std::string& rec, std::string& dat)
{
    int temp = 0;
    for (int i = 0; i <= message.size(); i++)
    {
        if (message[i] == ':')
        {
            temp = i;
            break;
        }
    }
    for (int j = 0; j < temp; j++)
    {
        rec += message[j];
    }
    for (int k = temp + 1; k <= message.size(); k++)
    {
        dat += message[k];
    }
}

void server::sendMessage(SOCKET sock)
{
    memset(buffer,0,SERVER_BUF);
    int rec = recv(sock, buffer, SERVER_BUF, 0);
    if (rec > 0)
    {
        std::string searchBuffer(buffer);
        std::string receiveClient, message;
        whoseMessage(searchBuffer, receiveClient, message);

        auto search = clientList.find(receiveClient);
        if (search != clientList.end())
        {
            std::string sendMessage = search->first;
            sendMessage += seperator + message;

            SOCKET sendMess = search->second;
            send(sendMess, sendMessage.c_str(), SERVER_BUF, 0);
        }
    }
}
