#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define PORT 8080
#define ADDR "127.0.0.1"
#include <iostream>
#include <sstream>
#include <fstream>
#include <winsock2.h>
#include <string>
#include "Server.hpp"


#pragma comment (lib, "ws2_32.lib")


int main() {
    
    Server::Server server;

    server.Start(ADDR, PORT);
    server.Listen();
    server.End();


    return 0;
}
