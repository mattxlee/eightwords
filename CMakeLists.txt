cmake_minimum_required(VERSION 3.2)

project(eightwords)

option(USE_CONAN "Use conan as the package manager" ON)

if (USE_CONAN)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
endif()

add_definitions(-std=c++11)

find_package(cxxopts REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(Iconv REQUIRED)

set(LIB_SRCS
    ./src/calendar.cpp
    ./src/eightwords.cpp
    ./src/face_converter.cpp
    )

set(CMD_SRCS
    ./src/main.cpp
    )

add_library(eightwords STATIC ${LIB_SRCS})
set_target_properties(eightwords PROPERTIES CXX_STANDARD 11)
target_compile_options(eightwords PUBLIC
    $<$<CONFIG:DEBUG>:-O0 -g>
    $<$<CONFIG:RELEASE>:-O3 -g>
    )
target_include_directories(eightwords PUBLIC
    ./include
    )

add_executable(eightwords_cli ${CMD_SRCS})
set_target_properties(eightwords_cli PROPERTIES CXX_STANDARD 11)
target_link_libraries(eightwords_cli
    eightwords cxxopts::cxxopts SQLite::SQLite3 Iconv::Iconv
    )
