project(OpenMIMOPlot)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(./vendor/glfw)

add_subdirectory(./vendor/glad)

include(imgui)
include(implot)

add_executable(OpenMIMOPlot ./OpenMIMOPlot/entry.cpp)

target_include_directories(OpenMIMOPlot PUBLIC IMPLOT_INCLUDE_DIR IMGUI_INCLUDE_DIR ./vendor/glfw/include ./vendor/glad/include)
target_link_libraries(OpenMIMOPlot PRIVATE implot imgui glad glfw)