#ifndef CLIENTIFC_H
#define CLIENTIFC_H

#include <string>

class ClientIfc
{
public:
    virtual bool Start() = 0;
    virtual bool ConnectToServer(int serverPort, std::string serverIp) = 0;
    virtual void ReceiveMsgFromServer() = 0;
    virtual bool Close() = 0;
    virtual bool SendMsg (std::string msg) = 0;
};
#endif // CLIENTIFC_H
