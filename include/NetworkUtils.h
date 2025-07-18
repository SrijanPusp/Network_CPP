#pragma once

// NetworkUtils.h: Yeh file common networking functions ko declare karti hai.
// Isse hum platform-specific code (jaise Windows ke liye Winsock) ko ek jagah rakh sakte hain.

// Function jo networking library ko initialize karega.
// Windows me iski zaroorat hoti hai (WSAStartup).
// Linux/macOS me iski zaroorat nahi hoti.
bool initializeNetworking();

// Function jo networking library ko saaf (cleanup) karega.
// Windows me iski zaroorat hoti hai (WSACleanup).
void cleanupNetworking();