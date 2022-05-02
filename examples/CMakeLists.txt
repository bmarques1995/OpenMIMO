cmake_minimum_required(VERSION 3.14)

project(OpenMIMO_SS)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../vendor/googletest)

add_executable(${PROJECT_NAME} ss_enter.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../include ../vendor/Eigen3)