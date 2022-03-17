#include <iostream>
#include "client.h"
#include <string>

int main(int argc,char *argv[])
{
    std::string clientName;

    if (argc == 2)
    {
         clientName = argv[1];
    }
    else
    {
        std::cout << "client ismi girilmedi!!" << std::endl;
        return 0;
    }
    

    client userClient(clientName);
    bool state = userClient.setupClient();
    if (state == 0)
        return 0;
        
    while (1)
    {
        std::string sendData;
        char *recData;
        std::cout << "data:  ";
        std::cin >> sendData;
        if (sendData == "close " + clientName)
        {
            break;
        }
        userClient.sendData(sendData);
        recData = userClient.receiveData();
        std::puts(recData);

    }

    userClient.closeClient();
}
