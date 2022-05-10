cmake_minimum_required(VERSION 3.20)

set(MyProjectName TestOpenMIMO)
project(${MyProjectName} C CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(../vendor/googletest binary_dir)

file(GLOB_RECURSE OPENMIMO_TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

foreach(X IN LISTS OPENMIMO_TEST_SOURCES)
    message(${X})
    message(" ")
endforeach()

add_executable(${MyProjectName} ${OPENMIMO_TEST_SOURCES})

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

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
if (CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    # we need to turn off optimization for non-skewed coverage reports
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

    # optional excludes - None needed here
    #    set(COVERAGE_EXCLUDES)

    # importantly, set the path to the gcovr executable that you downladed
    set(GCOVR_PATH "/home/ciaran/miniconda3/bin/gcovr")
    # Works
    setup_target_for_coverage_gcovr_xml(
            NAME TestOpenMIMOCoverageXml
            EXECUTABLE TestOpenMIMO
            DEPENDENCIES TestOpenMIMO OpenMIMO
    )
    # Works
    setup_target_for_coverage_gcovr_html(
            NAME TestOpenMIMOCoverageHtml
            EXECUTABLE TestOpenMIMO
            DEPENDENCIES TestOpenMIMO OpenMIMO
    )
    # This one did not work for me:
    setup_target_for_coverage_lcov(
            NAME TestOpenMIMOCoverageLcov
            EXECUTABLE TestOpenMIMO
            DEPENDENCIES TestOpenMIMO OpenMIMO
    )
endif ()