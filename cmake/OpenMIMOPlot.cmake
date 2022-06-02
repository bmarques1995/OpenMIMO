project(OpenMIMOPlot)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(./vendor/glfw)

add_subdirectory(./vendor/glad)

include(imgui)
include(implot)

file(GLOB_RECURSE PLOT_MIMO_CORE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Core/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_CORE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Core/*.hpp")

file(GLOB_RECURSE PLOT_MIMO_INTERFACE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/InterfaceGraphicsAPI/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_INTERFACE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/InterfaceGraphicsAPI/*.hpp")

file(GLOB_RECURSE PLOT_MIMO_LAYERS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/PlotLayers/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_LAYERS_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/PlotLayers/*.hpp")

file(GLOB_RECURSE PLOT_MIMO_UTILS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Utils/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_UTILS_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Utils/*.hpp")

file(GLOB_RECURSE PLOT_MIMO_EVENTS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Events/*.cpp")
file(GLOB_RECURSE PLOT_MIMO_EVENTS_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/Events/*.hpp")

set (WindowSources)
set (WindowHeaders)
set (GraphicsSources)
set (GraphicsHeaders)
set (ImGUISources)
set (ImGUIHeaders)

foreach(api IN LISTS WindowBackendsImplemented)
    if(${api} STREQUAL "GLFW")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Window/GLFW/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Window/GLFW/*.hpp")
        set(WindowSources ${WindowSources} ${TEMP_SOURCES})
        set(WindowHeaders ${WindowHeaders} ${TEMP_HEADERS})
    endif()
    if(${api} STREQUAL "WIN32API")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Window/WIN32/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Window/WIN32/*.hpp")
        set(WindowSources ${WindowSources} ${TEMP_SOURCES})
        set(WindowHeaders ${WindowHeaders} ${TEMP_HEADERS})
    endif()
endforeach()

foreach(api IN LISTS GraphicsBackendsImplemented)
    if("${api}" STREQUAL "GL4")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Graphics/GL4/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Graphics/GL4/*.hpp")
        set(GraphicsSources ${GraphicsSources} ${TEMP_SOURCES})
        set(GraphicsHeaders ${GraphicsHeaders} ${TEMP_HEADERS})
    endif()
    if("${api}" STREQUAL "D3D11")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Graphics/D3D11/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/Graphics/D3D11/*.hpp")
        set(GraphicsSources ${GraphicsSources} ${TEMP_SOURCES})
        set(GraphicsHeaders ${GraphicsHeaders} ${TEMP_HEADERS})
    endif()
endforeach()

foreach(api IN LISTS ImguiCombinedAPIS)
    if("${api}" STREQUAL "GLFWGL4")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/ImGUI/GLFWGL4/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/ImGUI/GLFWGL4/*.hpp")
        set(ImGUISources ${ImGUISources} ${TEMP_SOURCES})
        set(ImGUIHeaders ${ImGUIHeaders} ${TEMP_HEADERS})
    endif()
    if("${api}" STREQUAL "WIN32D3D11")
        file(GLOB_RECURSE TEMP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/ImGUI/WIN32D3D11/*.cpp")
        file(GLOB_RECURSE TEMP_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "OpenMIMOPlot/ImplementationGraphicsAPI/ImGUI/WIN32D3D11/*.hpp")
        set(ImGUISources ${ImGUISources} ${TEMP_SOURCES})
        set(ImGUIHeaders ${ImGUIHeaders} ${TEMP_HEADERS})
    endif()
endforeach()

set(PLOT_MIMO_SOURCES 
    
    ${PLOT_MIMO_CORE_SOURCES}
    ${PLOT_MIMO_LAYERS_SOURCES}
    ${PLOT_MIMO_INTERFACE_SOURCES}
    ${PLOT_MIMO_UTILS_SOURCES}
    ${PLOT_MIMO_EVENTS_SOURCES}
    ${WindowSources}
    ${GraphicsSources}
    ${ImGUISources} 
    OpenMIMOPlot/entry.cpp 
    OpenMIMOPlot/AppContainer.cpp
)
set(PLOT_MIMO_HEADERS
    ${PLOT_MIMO_CORE_HEADERS}
    ${PLOT_MIMO_LAYERS_HEADERS}
    ${PLOT_MIMO_INTERFACE_HEADERS}
    ${PLOT_MIMO_UTILS_HEADERS}
    ${PLOT_MIMO_EVENTS_HEADERS}
    ${WindowHeaders}
    ${GraphicsHeaders}
    ${ImGUIHeaders} 
    OpenMIMOPlot/GLSafeInclude.hpp
    OpenMIMOPlot/AppContainer.hpp
)

set(WinLibs)

if(WIN32)
    add_compile_definitions(WINDOWS_PLOT)
    set(WinLibs 
        "d3d11.lib"
        "d3dcompiler.lib"
        "gdi32.lib"
        "dxguid.lib"
    )
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        add_executable(OpenMIMOPlot WIN32 ${PLOT_MIMO_HEADERS} ${PLOT_MIMO_SOURCES})
    else()
        add_executable(OpenMIMOPlot ${PLOT_MIMO_HEADERS} ${PLOT_MIMO_SOURCES})
    endif()
else()
    add_executable(OpenMIMOPlot ${PLOT_MIMO_HEADERS} ${PLOT_MIMO_SOURCES})
endif()

target_include_directories(OpenMIMOPlot PRIVATE ./OpenMIMOPlot IMPLOT_INCLUDE_DIR IMGUI_INCLUDE_DIR ./vendor/glfw/include ./vendor/glad/include ./vendor/nlohmann_json/include)
target_link_libraries(OpenMIMOPlot PRIVATE implot imgui glad glfw ${WinLibs})