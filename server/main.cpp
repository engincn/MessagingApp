#include <iostream>
#include "server.h"

int main()
{
    server masterServer;
    masterServer.setupServer();
    while (1)
    {
        masterServer.connect();
    }
    masterServer.closeServer();
}
