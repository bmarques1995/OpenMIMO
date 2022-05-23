project(OpenMIMOPlot)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(./vendor/glfw)

add_subdirectory(./vendor/glad)

include(imgui)
include(implot)

file(GLOB_RECURSE PLOT_MIMO_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/*.hpp")

add_executable(OpenMIMOPlot ${PLOT_MIMO_HEADERS} ${PLOT_MIMO_SOURCES})

target_include_directories(OpenMIMOPlot PRIVATE ./OpenMIMOPlot IMPLOT_INCLUDE_DIR IMGUI_INCLUDE_DIR ./vendor/glfw/include ./vendor/glad/include)
target_link_libraries(OpenMIMOPlot PRIVATE implot imgui glad glfw)