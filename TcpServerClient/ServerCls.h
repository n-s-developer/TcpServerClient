#ifndef SERVERCLS_H
#define SERVERCLS_H

#include <ServerIfc.h>
#include <winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

class ServerCls : public ServerIfc
{
public:
    ServerCls();
    bool Start(int port, std::string ip) override;
    bool Bind() override;
    bool Listen() override;
    void Close() override;
    bool SendMsg (std::string msg) override;

    std::string Message;

private:
    void listenForClients();
    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    std::atomic<bool> isRunning; // Server çalışıyor mu?
    std::mutex mtx;

};

#endif // SERVERCLS_H
