#pragma once

#include <atomic>
#include <vector>   // <-- Added for std::vector
#include <thread>   // <-- Added for std::thread
#include <winsock2.h>
#include <ws2tcpip.h>

// HttpServer.h: Yeh file ek basic HTTP server class ko declare karti hai.

class HttpServer {
public:
    // Constructor: Server ko initial values deta hai.
    HttpServer();
    
    // Destructor: Agar server chal raha ho to use stop karta hai.
    ~HttpServer();

    // Server ko start karne ke liye function.
    // port: Jis port par server listen karega.
    void start(int port);

    // Server ko stop karne ke liye function.
    void stop();

private:
    // Naye client connection ko handle karne ke liye function.
    // Yeh function ek alag thread me chalega.
    // Changed SOCKET to socket_t for consistency
    void handleClient(socket_t clientSocket);

    using socket_t = SOCKET;
    socket_t serverSocket;
    std::atomic<bool> isRunning;
    static const socket_t INVALID_SOCKET_CONST;
    std::vector<std::thread> clientThreads;

    // Add helper method for thread error handling
    bool startClientThread(socket_t clientSocket);
};