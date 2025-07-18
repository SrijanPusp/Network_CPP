cmake_minimum_required(VERSION 3.10)

project(NetworkingProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    networking_app
    src/main.cpp
    src/NetworkUtils.cpp
    src/HttpServer.cpp
    src/TcpClient.cpp
)

# Agar Operating System Windows hai
if(WIN32)
  # Windows Sockets
  target_link_libraries(networking_app ws2_32)
else()
  # Linux/macOS ke liye
  target_link_libraries(networking_app pthread)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(STATUS "Executable will be created in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")