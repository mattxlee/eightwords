cmake_minimum_required(VERSION 3.10)

project(eightwords)

option(BUILD_TEST "Build test program" OFF)

find_package(Threads REQUIRED)

file(GLOB LIB_SRCS ./src/*.cpp)
add_library(eightwords STATIC ${LIB_SRCS})
target_compile_features(eightwords PUBLIC cxx_std_11)
target_include_directories(eightwords PUBLIC ./include)

if(BUILD_TEST)
  find_package(unofficial-sqlite3 CONFIG REQUIRED)
  find_package(GTest CONFIG REQUIRED)
  enable_testing()
  file(GLOB TEST_SRCS ./test/*.cpp)
  add_executable(eightwords_test ${TEST_SRCS})
  target_link_libraries(
    eightwords_test
    PRIVATE eightwords Threads::Threads unofficial::sqlite3::sqlite3 iconv
            GTest::gtest_main)
  add_test(NAME eightwords_test COMMAND eightwords_test)
endif()