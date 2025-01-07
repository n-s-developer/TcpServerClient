#ifndef SERVERCLS_H
#define SERVERCLS_H

#include <ServerIfc.h>
#include <winsock2.h>
#include <iostream>
#include <string>

class ServerCls : public ServerIfc
{
public:
    ServerCls();
    bool StartServer(std::string ip, int port) override;
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
};

#endif // SERVERCLS_H
