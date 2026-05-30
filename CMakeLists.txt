cmake_minimum_required(VERSION 3.28)

project(vcard
        VERSION 0.1
        DESCRIPTION "vCard - eine digitale Visitenkarte")

set(CMAKE_CXX_STANDARD 17)

add_executable(vcard src/main.cpp src/list.cpp)
target_include_directories(vcard PUBLIC include/)