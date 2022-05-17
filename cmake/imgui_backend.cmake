set(IMGUI_BACKEND_GLFW
    ../../vendor/imgui/backends/imgui_impl_glfw.cpp
    ../../vendor/imgui/backends/imgui_impl_glfw.h
)

set(IMGUI_BACKEND_WIN32API
    ../../vendor/imgui/backends/imgui_impl_win32.cpp
    ../../vendor/imgui/backends/imgui_impl_win32.h
)

set(IMGUI_BACKEND_SDL
    ../../vendor/imgui/backends/imgui_impl_sdl.cpp
    ../../vendor/imgui/backends/imgui_impl_sdl.h
)

set(IMGUI_BACKEND_OPENGL3
    ../../vendor/imgui/backends/imgui_impl_opengl3.cpp
    ../../vendor/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_BACKEND_VK 
    ../../vendor/imgui/backends/imgui_impl_vulkan.cpp
    ../../vendor/imgui/backends/imgui_impl_vulkan.h
)

set(IMGUI_BACKEND_D3D9 
    ../../vendor/imgui/backends/imgui_impl_dx9.cpp
    ../../vendor/imgui/backends/imgui_impl_dx9.h
)

set(IMGUI_BACKEND_D3D11 
    ../../vendor/imgui/backends/imgui_impl_dx11.cpp
    ../../vendor/imgui/backends/imgui_impl_dx11.h
)

set(IMGUI_BACKEND_D3D12 
    ../../vendor/imgui/backends/imgui_impl_dx12.cpp
    ../../vendor/imgui/backends/imgui_impl_dx12.h
)

set(IMGUI_BACKEND_METAL 
    ../../vendor/imgui/backends/imgui_impl_metal.mm
    ../../vendor/imgui/backends/imgui_impl_metal.h
)

set(WindowBackend GLFW CACHE STRING "Window API VAlue")
set(GraphicsBackend GL3 CACHE STRING "Graphics API Value")

set(WindowBackends GLFW WIN32API SDL)
set(GraphicsBackends GL3 VK D3D9 D3D11 D3D12 METAL)

if(WindowBackend STREQUAL "WIN32")
    set(WindowBackend WIN32API)
endif()

if(NOT WindowBackend IN_LIST WindowBackends)
    message(FATAL_ERROR "Window API not implemented in ImGUI, you must implementate it")
else()
    message("Window API supported")
endif()

if(NOT GraphicsBackend IN_LIST GraphicsBackends)
    message(FATAL_ERROR "Graphics API not implemented in ImGUI, you must implementate it")
else()
    message("Graphics API supported")
endif()

set(window_source OFF)
set(graphics_source OFF)

if(WindowBackend STREQUAL "GLFW")
    set(window_source ${IMGUI_BACKEND_GLFW})
elseif(WindowBackend STREQUAL "WIN32API")
    set(window_source ${IMGUI_BACKEND_WIN32API})
elseif(WindowBackend STREQUAL "SDL")
    set(window_source ${IMGUI_BACKEND_SDL})
endif()

if(GraphicsBackend STREQUAL "GL3")
    set(graphics_source ${IMGUI_BACKEND_OPENGL3})
elseif(GraphicsBackend STREQUAL "VK")
    set(graphics_source ${IMGUI_BACKEND_VK})
elseif(GraphicsBackend STREQUAL "D3D9")
    set(graphics_source ${IMGUI_BACKEND_D3D9})
elseif(GraphicsBackend STREQUAL "D3D11")
    set(graphics_source ${IMGUI_BACKEND_D3D11})
elseif(GraphicsBackend STREQUAL "D3D12")
    set(graphics_source ${IMGUI_BACKEND_D3D12})
elseif(GraphicsBackend STREQUAL "METAL")
    set(graphics_source ${IMGUI_BACKEND_METAL})
endif()

set(IMGUI_IMPLEMENT ${graphics_source} ${window_source})
