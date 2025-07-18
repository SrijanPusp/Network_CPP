#include <iostream>
#include <string>
#include "HttpServer.h"
#include "TcpClient.h"

// main.cpp: Yeh program ka entry point hai.

void runServer() {
    HttpServer server;
    // Server ko port 8080 par start karte hain.
    // Aap `Ctrl+C` press karke server ko band kar sakte hain.
    server.start(8080);
}

void runClient() {
    TcpClient client;
    // Localhost par chal rahe server se connect karte hain.
    if (client.connectToServer("127.0.0.1", 8080)) {
        // Ek simple HTTP GET request banate hain.
        std::string request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
        std::cout << "\nSending request to server:\n" << request << std::endl;
        
        // Request bhejte hain.
        client.sendData(request);
        
        // Server se response receive karte hain.
        std::string response = client.receiveData();
        std::cout << "\nReceived response from server:\n" << response << std::endl;
        
        // Connection band karte hain.
        client.closeConnection();
    } else {
        std::cout << "Could not connect to the server. Pehle server run karein." << std::endl;
    }
}

int main() {
    // User se puchte hain ki woh kya run karna chahta hai.
    std::cout << "Networking Project 🚀" << std::endl;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Run as HTTP Server" << std::endl;
    std::cout << "2. Run as TCP Client" << std::endl;
    std::cout << "Enter choice (1 or 2): ";

    char choice;
    std::cin >> choice;

    if (choice == '1') {
        runServer();
    } else if (choice == '2') {
        runClient();
    } else {
        std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
    }

    return 0;
}