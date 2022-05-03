cmake_minimum_required(VERSION 3.14)

project(OpenMIMO_SS)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ss_enter.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/Eigen3 ../include)