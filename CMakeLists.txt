cmake_minimum_required(VERSION 2.8.4)

project(eightwords)

message(STATUS "Current system ${CMAKE_SYSTEM_NAME}")

add_definitions(-std=c++11)

include_directories(
    "./include"
    )

file(GLOB src "./src/*.cpp")

add_executable(eightwords ${src})

find_package(Boost 1.54 REQUIRED program_options)

if (APPLE)
  message(STATUS "Apple needs linking libiconv")
  set(ICONVLIB "iconv")
endif(APPLE)

target_link_libraries(eightwords sqlite3 ${ICONVLIB} ${Boost_LIBRARIES})
