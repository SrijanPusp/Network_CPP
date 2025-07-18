# C++ Networking Project 🌐

Yeh ek simple C++ networking project hai jo TCP Client aur HTTP Server ka basic implementation dikhata hai. Yeh project cross-platform hai aur Windows, Linux, aur macOS par chal sakta hai.

Code ko beginner-friendly rakha gaya hai aur Hinglish comments add kiye gaye hain taaki concepts aasani se samajh aa sakein.

## Features ✨

* **TCP Client**: Ek server se connect karke message bhej sakta hai.
* **HTTP Server**: Multiple clients se connections accept kar sakta hai aur basic HTTP GET requests ka "Hello World!" me jawab deta hai.
* **Cross-Platform**: Windows (Winsock) aur Linux/macOS (Berkeley Sockets) dono par kaam karta hai.
* **CMake Build System**: Project ko build karne ke liye modern CMake ka use kiya gaya hai.

## Build Kaise Karein 🛠️

Aapke system me C++ compiler aur CMake installed hona chahiye.

1.  **Repository Clone Karein (ya files copy karein)**
2.  **Build Directory Banayein**:
    ```bash
    mkdir build
    cd build
    ```
3.  **CMake se Build Files Generate Karein**:
    ```bash
    cmake ..
    ```
4.  **Project ko Compile Karein**:
    ```bash
    cmake --build .
    ```

    Iske baad `build` directory ke andar aapko `networking_app` (ya `networking_app.exe` Windows par) file mil jayegi.

## Run Kaise Karein 🚀

Executable ko command line se run karein.

```bash
./networking_app