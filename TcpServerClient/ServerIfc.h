#ifndef SERVERIFC_H
#define SERVERIFC_H

#include <string>

class ServerIfc
{
public:
    virtual bool Start(int port, std::string ip) = 0;
    virtual bool Bind() = 0;
    virtual bool Listen() = 0;
    virtual void Close() = 0;
    virtual bool SendMsg (std::string msg) = 0;
};

#endif // SERVERIFC_H
