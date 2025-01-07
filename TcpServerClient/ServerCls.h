#ifndef SERVERCLS_H
#define SERVERCLS_H

#include <ServerIfc.h>
#include <winsock2.h>
#include <iostream>

class ServerCls : public ServerIfc
{
public:
    ServerCls();
    bool StartServer(int port) override;
    bool BindServer() override;

public:
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
};

#endif // SERVERCLS_H
