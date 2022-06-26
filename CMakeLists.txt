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

file(GLOB src "./src/*.cpp")

add_executable(eightwords ${src})

target_link_libraries(eightwords cxxopts::cxxopts SQLite::SQLite3 Iconv::Iconv)
