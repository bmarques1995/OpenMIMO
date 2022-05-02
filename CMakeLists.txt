cmake_minimum_required(VERSION 3.14)

add_subdirectory("vendor/googletest")

option(RUN_TESTS "Specifies if the tests will run" ON)

set(CMAKE_CXX_STANDARD 20)

