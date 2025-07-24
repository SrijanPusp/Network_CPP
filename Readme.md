# C++ Foundational Networking Project (under development)

## Description

This project is a fundamental implementation of a TCP Client and an HTTP Server in C++. It was developed as a hands-on learning exercise to understand the core principles of network programming. The primary goal was to build a simple, cross-platform networking application from the ground up, focusing on foundational concepts and clear, maintainable code.

This repository is intended to showcase a solid understanding of C++ and basic networking APIs.

## Project Focus & Learning Goals

As a learning-focused project, the key objectives were:

* **Mastering Core C++:** To apply modern C++ principles in a practical, real-world scenario.
* **Understanding Network Fundamentals:** To gain a deep understanding of TCP/IP, sockets, and the client-server architecture.
* **Cross-Platform Development:** To learn how to write portable code that works on different operating systems (Windows and Unix-like systems) by handling their distinct networking APIs (Winsock and Berkeley Sockets).
* **Modern Build Systems:** To utilize CMake for managing the build process in a clean and scalable way.

## Features ✨

* **TCP Client:** A simple client capable of establishing a connection to a server and transmitting messages.
* **HTTP Server:** A basic multi-threaded server that can accept connections from multiple clients and respond to GET requests with a standard "Hello, World!" message.
* **Cross-Platform Compatibility:** Designed to compile and run on Windows, Linux, and macOS.
* **CMake Build System:** Uses modern CMake for easy project configuration and compilation.

## Technologies Used

* **Language:** C++
* **Networking APIs:** Winsock (Windows), Berkeley Sockets (Linux, macOS)
* **Build System:** CMake

## Getting Started

### Prerequisites

Ensure you have a C++ compiler and CMake installed on your system.

### Build Instructions 🛠️

1.  **Clone the repository:**
    ```bash
    git clone [your-repository-link]
    cd [repository-folder]
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Generate the build files using CMake:**
    ```bash
    cmake ..
    ```

4.  **Compile the project:**
    ```bash
    cmake --build .
    ```
    This will create an executable file named `networking_app` (`networking_app.exe` on Windows) inside the `build` directory.

## How to Run 🚀

Execute the application from the command line:

```bash
./networking_app
