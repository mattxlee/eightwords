cmake_minimum_required(VERSION 2.8.4)

project(eightwords)

add_definitions(-std=c++11)

include_directories(
    "./include"
    )

file(GLOB src "./src/*.cpp")

add_executable(eightwords ${src})

find_package(Boost 1.54 REQUIRED program_options)

target_link_libraries(eightwords iconv sqlite3 ${Boost_LIBRARIES})
