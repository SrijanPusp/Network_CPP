#include "HttpServer.h"
#include "NetworkUtils.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>

// Platform-specific headers
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h> // close()
#endif


// Static member definition
#ifdef _WIN32
    const HttpServer::socket_t HttpServer::INVALID_SOCKET_CONST = INVALID_SOCKET;
#else
    const HttpServer::socket_t HttpServer::INVALID_SOCKET_CONST = -1;
#endif

// Constructor
HttpServer::HttpServer() : serverSocket(INVALID_SOCKET_CONST), isRunning(false) {}

// Destructor
HttpServer::~HttpServer() {
    stop();
}

void HttpServer::start(int port) {
    // Networking ko initialize karte hain
    if (!initializeNetworking()) {
        std::cerr << "Failed to initialize networking." << std::endl;
        return;
    }

    // Server socket banate hain
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET_CONST) {
        std::cerr << "Error: Server socket creation failed." << std::endl;
        cleanupNetworking();
        return;
    }

    // Server ka address structure set karte hain
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Kisi bhi available network interface par listen karega
    serverAddr.sin_port = htons(port); // Port number set karte hain

    // Socket ko address aur port se bind karte hain
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Bind failed." << std::endl;
        stop();
        return;
    }

    // Incoming connections ke liye listen karna shuru karte hain
    // 10: backlog queue ka size, yaani ek saath kitne pending connections ho sakte hain
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "Error: Listen failed." << std::endl;
        stop();
        return;
    }
    isRunning = true;
    std::cout << "Server started on port " << port << ". Waiting for connections..." << std::endl;

    while (isRunning) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET_CONST) {
            if (isRunning) {
                std::cerr << "Error: Accept failed." << std::endl;
            }
            continue;
        }

        std::cout << "New connection accepted." << std::endl;

        // debugged* to be reviewed later**
        clientThreads.emplace_back(&HttpServer::handleClient, this, clientSocket);
    }
}

void HttpServer::stop() {
    if (isRunning) {
        isRunning = false;

        // Close the server socket to unblock the `accept` call in the start() loop
        if (serverSocket != INVALID_SOCKET_CONST) {
            closesocket(serverSocket);
            serverSocket = INVALID_SOCKET_CONST;
        }

        // *review*
        std::cout << "Waiting for client threads to finish..." << std::endl;
        for (auto& thread : clientThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        clientThreads.clear(); // Clear the vector after joining

        cleanupNetworking();
        std::cout << "Server stopped." << std::endl;
    }
}

void HttpServer::handleClient(socket_t clientSocket) {
    std::vector<char> buffer(4096);
    int bytesReceived = recv(clientSocket, buffer.data(), buffer.size(), 0);

    if (bytesReceived > 0) {
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 45\r\n\r\n<html><body><h1>Hello from C++ Server!</h1></body></html>";
        send(clientSocket, response.c_str(), response.length(), 0);
    } else if (bytesReceived == 0) {
        std::cout << "Client disconnected." << std::endl;
    } else {
        std::cerr << "Error in recv." << std::endl;
    }

    closesocket(clientSocket);
}
