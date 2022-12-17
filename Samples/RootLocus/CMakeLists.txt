cmake_minimum_required(VERSION 3.20)

project(RootLocusSample LANGUAGES CXX)

add_executable(RootLocusSample rlocus.cpp)
target_include_directories(RootLocusSample PRIVATE ../../include/ ../../vendor/Eigen3)