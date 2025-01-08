#ifndef CLIENTCLS_H
#define CLIENTCLS_H

#include <ClientIfc.h>
#include <string>
#include <thread>
#include <winsock2.h>
#include <iostream>
#include <atomic>
#include <mutex>

class ClientCls : public ClientIfc
{
public:
    ClientCls();

    bool Start() override;
    bool ConnectToServer(int serverPort, std::string serverIp) override;
    void ReceiveMsgFromServer() override;
    bool Close() override;
    bool SendMsg (std::string msg) override;
    std::string Message;

private:
    void listenForServer();
    SOCKET clientSocket;
    std::atomic<bool> isRunning; // Server çalışıyor mu?
    std::mutex mtx;
};

#endif // CLIENTCLS_H
