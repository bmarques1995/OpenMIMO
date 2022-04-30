cmake_minimum_required(VERSION 3.5)

project(OpenMIMO_SS)

add_executable(${PROJECT_NAME} examples/ss_enter.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include vendor/Eigen3)