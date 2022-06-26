cmake_minimum_required(VERSION 3.2)

project(eightwords)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_definitions(-std=c++11)

find_package(cxxopts REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Iconv REQUIRED)

include_directories(
    "./include"
    )

set(LIB_SRCS
    ./src/calendar.cpp
    ./src/eightwords.cpp
    ./src/face_converter.cpp
    )

set(CMD_SRCS
    ./src/main.cpp
    )

add_library(eightwords STATIC ${LIB_SRCS})

add_executable(eightwords_cli ${CMD_SRCS})

target_link_libraries(eightwords_cli eightwords cxxopts::cxxopts SQLite::SQLite3 Iconv::Iconv)
