set(MyProjectName TestOpenMIMO)
project(${MyProjectName} C CXX)
set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(./vendor/googletest)

file(GLOB_RECURSE OPENMIMO_TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "tests/*.cpp")

foreach(X IN LISTS OPENMIMO_TEST_SOURCES)
    message(${X})
endforeach()

add_executable(${MyProjectName} ${OPENMIMO_TEST_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./include ./vendor/Eigen3)

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

#MSVC auto config to follow googletest

option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)
if (MSVC)
    # For MSVC, CMake sets certain flags to defaults we want to override.
    # This replacement code is taken from sample in the CMake Wiki at
    # https://gitlab.kitware.com/cmake/community/wikis/FAQ#dynamic-replace.
    foreach (flag_var
            CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if (NOT BUILD_SHARED_LIBS AND NOT gtest_force_shared_crt)
        # When Google Test is built as a shared library, it should also use
        # shared runtime libraries.  Otherwise, it may end up with multiple
        # copies of runtime library data in different modules, resulting in
        # hard-to-find crashes. When it is built as a static library, it is
        # preferable to use CRT as static libraries, as we don't have to rely
        # on CRT DLLs being available. CMake always defaults to using shared
        # CRT libraries, so we override that default here.
        string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
    endif()

    # We prefer more strict warning checking for building Google Test.
    # Replaces /W3 with /W4 in defaults.
    string(REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")

    # Prevent D9025 warning for targets that have exception handling
    # turned off (/EHs-c- flag). Where required, exceptions are explicitly
    # re-enabled using the cxx_exception_flags variable.
    endforeach()
endif()

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