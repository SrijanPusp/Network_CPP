#pragma once

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

// TcpClient.h: Yeh class ek simple TCP client ko manage karne ke liye hai.

class TcpClient {
public:
    // Constructor: Naya client object banata hai.
    TcpClient();
    
    // Destructor: Connection close aur resources free karta hai.
    ~TcpClient();

    // Server se connect karne ke liye function.
    // ip: Server ka IP address.
    // port: Server ka port number.
    // return: Connection successful hua toh true, varna false.
    bool connectToServer(const std::string& ip, int port);

    // Server ko data bhejne ke liye function.
    // data: Bheja jaane wala message.
    // return: Data successfully bheja gaya toh true, varna false.
    bool sendData(const std::string& data);

    // Server se data receive karne ke liye function.
    // bufferSize: Ek baar me kitna data padhna hai.
    // return: Server se mila hua data. Agar error hua toh empty string.
    std::string receiveData(int bufferSize = 4096);

    // Connection ko band karne ke liye function.
    void closeConnection();

private:
    using socket_t = SOCKET;
    socket_t sock;
    
    // Invalid socket ki value. Cross-platform compatibility ke liye.
    static const socket_t INVALID_SOCKET_CONST;
};