cmake_minimum_required(VERSION 3.14)

set(MyProjectName TestSample)

project(${MyProjectName} C CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(../vendor/googletest binary_dir)

add_executable(${MyProjectName} DynamicSystem.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../include ../vendor/Eigen3)

target_link_libraries(
    ${MyProjectName} 
    PRIVATE 
    gtest_main
    gtest
    gmock_main
    gmock
)

add_test(
    NAME ${MyProjectName}
    COMMAND ${MyProjectName}
)