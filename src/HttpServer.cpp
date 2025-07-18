#include "HttpServer.h"
#include "NetworkUtils.h" // Assuming this contains initialize/cleanupNetworking
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

const HttpServer::socket_t HttpServer::INVALID_SOCKET_CONST = INVALID_SOCKET;

HttpServer::HttpServer() : serverSocket(INVALID_SOCKET_CONST), isRunning(false) {}

HttpServer::~HttpServer() {
    stop();
}

void HttpServer::start(int port) {
    // ... (Your existing setup code for socket, bind, listen is correct) ...
    // ... (Keep it as is until the while loop) ...

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

        // **CHANGE HERE: Store the thread instead of detaching**
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

        // **CHANGE HERE: Wait for all client threads to finish**
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
    // This implementation is fine as is.
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