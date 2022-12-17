cmake_minimum_required(VERSION 3.20)

project(BodeSample LANGUAGES CXX)

add_executable(BodeSample bode.cpp)
target_include_directories(BodeSample PRIVATE ../../include/ ../../vendor/Eigen3)