set(IMPLOT_HEADERS vendor/implot/implot.h vendor/implot/implot_internal.h)
set(IMPLOT_SRC     vendor/implot/implot.cpp vendor/implot/implot_items.cpp vendor/implot/implot_demo.cpp)
set(IMPLOT_INCLUDE_DIR ./vendor/implot)

add_library(implot STATIC ${IMPLOT_SRC} ${IMPLOT_HEADERS})
target_include_directories(implot PUBLIC ${IMGUI_INCLUDE_DIR} ${IMPLOT_INCLUDE_DIR})
target_link_libraries(implot PRIVATE imgui)