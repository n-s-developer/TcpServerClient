#include "ServerCls.h"

ServerCls::ServerCls()
{

}

bool ServerCls::Start(int port, std::string ip)
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
    // serverAddr.sin_addr.s_addr = INADDR_ANY; // Herhangi bir IP adresi
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str() );

    return true;
}

bool ServerCls::Bind()
{
    // Sunucu soketini bağla
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        // std::cerr << "Bind hatası!" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    return true;
}

bool ServerCls::Listen()
{
    // Bağlantı taleplerini dinle
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    isRunning.store(true);

    // Bağlantı geldiğinde yeni bir iş parçacığı başlat
    std::thread listenThread(&ServerCls::listenForClients, this);
    listenThread.detach();  // İş parçacığını ayırarak ana iş parçacığından bağımsız çalışmasını sağlıyoruz.

    return true;
}

void ServerCls::Close()
{
    isRunning.store(false);
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
    }
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
}

void ServerCls::listenForClients()
{
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    while (isRunning.load()) {
        // Bağlantı bekleyin
        SOCKET newClientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (newClientSocket == INVALID_SOCKET) {
            std::cerr << "Client connection failed!" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(mtx);  // Mutex kullanarak güvenli işlem
        clientSocket = newClientSocket;

        std::cout << "istemci baglandi!" << std::endl;

        // Mesaj dinlemeye başla
        char buffer[1024];
        int bytesReceived;
        while ((bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
            buffer[bytesReceived] = '\0';  // Gelen veriyi null terminator ile sonlandır
            Message += buffer;

            std::cout << "Server Mesaj Aldı: "<< buffer << std::endl;
        }

        // Bağlantı kesildi
        if (bytesReceived == 0) {
            std::cout << "İstemci bağlantısı kapandı." << std::endl;
        } else if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Mesaj alınamadı." << std::endl;
        }

        closesocket(clientSocket);
    }
}


bool ServerCls::SendMsg (std::string msg)
{
    if (clientSocket != INVALID_SOCKET) {
        std::lock_guard<std::mutex> lock(mtx);  // Mutex kullanarak güvenli veri aktarımı
        int result = send(clientSocket, msg.c_str(), msg.length(), 0);
        return result != SOCKET_ERROR;
    }
    return false;
}
