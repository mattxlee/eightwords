cmake_minimum_required(VERSION 3.2)

project(eightwords)

include(FetchContent)
FetchContent_Declare(cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts
    GIT_TAG v3.0.0
    )
FetchContent_MakeAvailable(cxxopts)

set(THIRD ${CMAKE_BINARY_DIR}/third)

find_package(Threads REQUIRED)

include(ExternalProject)
ExternalProject_Add(Iconv
    PREFIX ${THIRD}
    URL https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.17.tar.gz
    URL_HASH SHA256=8f74213b56238c85a50a5329f77e06198771e70dd9a739779f4c02f65d971313
    CONFIGURE_COMMAND ./configure --prefix=${THIRD}
    BUILD_IN_SOURCE 1
    )
set(ICONV_LIBRARIES ${THIRD}/lib/libcharset.a ${THIRD}/lib/libiconv.so)

ExternalProject_Add(SQLite3
    PREFIX ${THIRD}
    URL https://www.sqlite.org/2022/sqlite-amalgamation-3390200.zip
    URL_HASH SHA256=87775784f8b22d0d0f1d7811870d39feaa7896319c7c20b849a4181c5a50609b
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    )

set(SQLITE3_SRCS ${THIRD}/src/SQLite3/sqlite3.c)
set_source_files_properties(${SQLITE3_SRCS} PROPERTIES GENERATED TRUE)
add_library(sqlite ${SQLITE3_SRCS})
add_dependencies(sqlite SQLite3)

include_directories(
    ${THIRD}/include
    ${THIRD}/src/SQLite3
    ./include
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
set_target_properties(eightwords PROPERTIES CXX_STANDARD 11)
target_compile_options(eightwords PUBLIC
    $<$<CONFIG:DEBUG>:-O0 -g>
    $<$<CONFIG:RELEASE>:-O3 -g>
    )
target_include_directories(eightwords PUBLIC
    ./include
    )

add_executable(eightwords_cli ${CMD_SRCS})
add_dependencies(eightwords_cli Iconv)
set_target_properties(eightwords_cli PROPERTIES CXX_STANDARD 11)
target_link_libraries(eightwords_cli
    eightwords cxxopts::cxxopts ${ICONV_LIBRARIES} sqlite Threads::Threads dl
    )
