#include "NetworkUtils.h"
#include <winsock2.h>

bool initializeNetworking() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    return result == 0;
}

void cleanupNetworking() {
    WSACleanup();
}