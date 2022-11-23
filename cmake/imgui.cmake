set(IMGUI_HEADERS
    ./vendor/imgui/imconfig.h
    ./vendor/imgui/imgui_internal.h
    ./vendor/imgui/imgui.h
    ./vendor/imgui/imstb_rectpack.h
    ./vendor/imgui/imstb_textedit.h
    ./vendor/imgui/imstb_truetype.h
)

set(IMGUI_SRC
    ./vendor/imgui/imgui_demo.cpp
    ./vendor/imgui/imgui_draw.cpp
    ./vendor/imgui/imgui_tables.cpp
    ./vendor/imgui/imgui_widgets.cpp
    ./vendor/imgui/imgui.cpp
)

include(imgui_backend)

set(IMGUI_INCLUDE_DIR ./vendor/imgui ./vendor/glad/include ./vendor/glfw/include)

add_library(imgui STATIC ${IMGUI_SRC} ${IMGUI_HEADERS} ${IMGUI_IMPLEMENT})
target_include_directories(imgui PRIVATE ${IMGUI_INCLUDE_DIR})
