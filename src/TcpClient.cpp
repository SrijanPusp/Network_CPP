// Remove #pragma once from the top

#pragma once

// Platform-specific headers must be included first on Windows to avoid conflicts.
#ifdef _WIN32
    // Define the minimum Windows version required for inet_pton (Vista and newer).
    #define _WIN32_WINNT 0x0600
    #include <winsock2.h>
    #include <ws2tcpip.h> // inet_pton is declared here for Windows.
    // Tell the linker to link against the Winsock library.
    #pragma comment(lib, "ws2_32.lib") 
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h> // inet_pton is declared here for POSIX.
    #include <unistd.h>    // For the close() function.
#endif

#include "TcpClient.h"
#include "NetworkUtils.h"
#include <iostream>
#include <vector>

// Define the static member for an invalid socket.
#ifdef _WIN32
    const TcpClient::socket_t TcpClient::INVALID_SOCKET_CONST = INVALID_SOCKET;
#else
    const TcpClient::socket_t TcpClient::INVALID_SOCKET_CONST = -1;
#endif


// Constructor: Initializes the object and networking.
TcpClient::TcpClient() : sock(INVALID_SOCKET_CONST) {
    initializeNetworking(); // Initialize the networking library.
}

// Destructor: Ensures the connection is closed and networking is cleaned up.
TcpClient::~TcpClient() {
    closeConnection();
    cleanupNetworking(); // Clean up the networking library.
}

bool TcpClient::connectToServer(const std::string& ip, int port) {
    if (sock != INVALID_SOCKET_CONST) {
        closeConnection();
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET_CONST) {
        std::cerr << "Error: Socket creation failed." << std::endl;
        return false;
    }

    // Set timeout for operations
    DWORD timeout = 5000; // 5 seconds
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

    // Zero out the structure
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    int ipResult = inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
    if (ipResult == 0) {
        std::cerr << "Error: Invalid IP address format." << std::endl;
        closeConnection();
        return false;
    } else if (ipResult == -1) {
        std::cerr << "Error: System error occurred while converting IP address." << std::endl;
        closeConnection();
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Connection failed." << std::endl;
        closeConnection();
        return false;
    }

    std::cout << "Successfully connected to server at " << ip << ":" << port << std::endl;
    return true;
}

bool TcpClient::sendData(const std::string& data) {
    if (sock == INVALID_SOCKET_CONST) {
        std::cerr << "Error: Not connected to any server." << std::endl;
        return false;
    }

    size_t totalSent = 0;
    while (totalSent < data.length()) {
        int bytesSent = send(sock, data.c_str() + totalSent, data.length() - totalSent, 0);
        if (bytesSent < 0) {
            std::cerr << "Error: Failed to send data." << std::endl;
            return false;
        }
        totalSent += bytesSent;
    }
    return true;
}

std::string TcpClient::receiveData(int bufferSize) {
    if (sock == INVALID_SOCKET_CONST) {
        std::cerr << "Error: Not connected to any server." << std::endl;
        return "";
    }

    // Create a buffer to store the received data.
    std::vector<char> buffer(bufferSize);
    
    // The recv() function receives data from the server.
    int bytesReceived = recv(sock, buffer.data(), bufferSize, 0);
    
    if (bytesReceived > 0) {
        // Return the received data as a string.
        return std::string(buffer.data(), bytesReceived);
    } else if (bytesReceived == 0) {
        // The server has closed the connection.
        std::cout << "Server closed the connection." << std::endl;
        return "";
    } else {
        // An error occurred during recv.
        std::cerr << "Error: recv failed." << std::endl;
        return "";
    }
}

void TcpClient::closeConnection() {
    // If the socket is open, close it.
    if (sock != INVALID_SOCKET_CONST) {
        #ifdef _WIN32
            closesocket(sock);
        #else
            close(sock);
        #endif
        sock = INVALID_SOCKET_CONST;
    }
}
