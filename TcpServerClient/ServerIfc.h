#ifndef SERVERIFC_H
#define SERVERIFC_H

#include <string>

class ServerIfc
{
    virtual bool StartServer(std::string ip, int port) = 0;
};

#endif // SERVERIFC_H
