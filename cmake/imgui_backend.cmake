set(IMGUI_BACKEND_GLFW
    ../../vendor/imgui/backends/imgui_impl_glfw.cpp
    ../../vendor/imgui/backends/imgui_impl_glfw.h
)

# set(IMGUI_BACKEND_WIN32API
#     ../../vendor/imgui/backends/imgui_impl_win32.cpp
#     ../../vendor/imgui/backends/imgui_impl_win32.h
# )

# set(IMGUI_BACKEND_SDL
#     ../../vendor/imgui/backends/imgui_impl_sdl.cpp
#     ../../vendor/imgui/backends/imgui_impl_sdl.h
# )

set(IMGUI_BACKEND_OPENGL3
    ../../vendor/imgui/backends/imgui_impl_opengl3.cpp
    ../../vendor/imgui/backends/imgui_impl_opengl3.h
)

# set(IMGUI_BACKEND_VK 
#     ../../vendor/imgui/backends/imgui_impl_vulkan.cpp
#     ../../vendor/imgui/backends/imgui_impl_vulkan.h
# )

# set(IMGUI_BACKEND_D3D9 
#     ../../vendor/imgui/backends/imgui_impl_dx9.cpp
#     ../../vendor/imgui/backends/imgui_impl_dx9.h
# )

# set(IMGUI_BACKEND_D3D11 
#     ../../vendor/imgui/backends/imgui_impl_dx11.cpp
#     ../../vendor/imgui/backends/imgui_impl_dx11.h
# )

# set(IMGUI_BACKEND_D3D12 
#     ../../vendor/imgui/backends/imgui_impl_dx12.cpp
#     ../../vendor/imgui/backends/imgui_impl_dx12.h
# )

# set(IMGUI_BACKEND_METAL 
#     ../../vendor/imgui/backends/imgui_impl_metal.mm
#     ../../vendor/imgui/backends/imgui_impl_metal.h
# )

set(WindowBackends)
set(WindowBackends ${WindowBackends} ${IMGUI_BACKEND_GLFW})

set(GraphicsBackends)
set(GraphicsBackends ${GraphicsBackends} ${IMGUI_BACKEND_OPENGL3})


set(IMGUI_IMPLEMENT ${WindowBackends} ${GraphicsBackends})
