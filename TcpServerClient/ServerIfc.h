#ifndef SERVERIFC_H
#define SERVERIFC_H

#include <string>

class ServerIfc
{
    virtual bool StartServer(int port) = 0;
    virtual bool BindServer() = 0;
};

#endif // SERVERIFC_H
