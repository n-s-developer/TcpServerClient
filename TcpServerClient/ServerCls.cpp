#include "ServerCls.h"

ServerCls::ServerCls()
{

}

bool ServerCls::StartServer(std::string ip, int port)
{

    // Winsock'i başlat
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // std::cerr << "Winsock başlatılamadı!" << std::endl;
        return false;
    }

    // Sunucu soketini oluştur
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        // std::cerr << "Soket oluşturulamadı!" << std::endl;
        WSACleanup();
        return false;
    }

    // Sunucu adresini yapılandır
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = std::stoul(ip); // Herhangi bir IP adresi

    return true;
}
