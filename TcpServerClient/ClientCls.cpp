#include "ClientCls.h"

ClientCls::ClientCls()
{

}

bool ClientCls::Start()
{
    // Winsock başlat
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return false;
    }

    // İstemci soketi oluştur
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        WSACleanup();
        return false;
    }

    return true;
}

bool ClientCls::ConnectToServer(int serverPort, std::string serverIp)
{
    // Sunucu adresi ayarları
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;              // IPv4
    serverAddr.sin_addr.s_addr = inet_addr(serverIp.c_str() ); // Sunucu IP adresi (localhost)
    serverAddr.sin_port = htons(serverPort);            // Sunucu port numarası

    // Sunucuya bağlan
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Sunucuya bağlanılamadı." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    return true;
}

void ClientCls::ReceiveMsgFromServer()
{

    isRunning.store(true); // Client başlatıldığında isRunning true yapılır
    std::cout << "Client is running..." << std::endl;

    // Listen fonksiyonunu thread içinde başlatıyoruz
    std::thread clientThread = std::thread(&ClientCls::listenForServer, this); // Dinlemeyi başlatıyoruz
}

bool ClientCls::Close()
{
    isRunning.store(false); // Client bağlantısını kes

    // İstemci soketini kapat
    closesocket(clientSocket);

    // Winsock temizle
    WSACleanup();

    return true;
}

bool ClientCls::SendMsg (std::string msg)
{
    if (isRunning.load())
    {
        // Bağlantı açıldığında, mesajı gönder
        const char* message = msg.c_str();

        // Mesajı gönder
        int sendResult = send(clientSocket, message, static_cast<int>(msg.length()), 0);
        if (sendResult == SOCKET_ERROR) {
            std::cerr << "Mesaj gönderilemedi!" << std::endl;
        } else {
            std::cout << "Mesaj gönderildi: " << msg << std::endl;
        }
    }
    else
    {
        std::cerr << "Client bağlantısı yok, mesaj gönderilemedi!" << std::endl;
    }
    return true;
}

void ClientCls::listenForServer()
{
    // Bağlantı işlemleri burada
    while (isRunning.load()) {
        char buffer[1024] = {0};
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0)
        {
            Message += buffer;
        }
        else
        {
            std::cerr << "Sunucudan mesaj alınamadı." << std::endl;
        }
    }
}
