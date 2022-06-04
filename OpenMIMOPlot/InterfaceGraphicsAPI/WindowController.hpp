#ifndef WINDOW_CONTROLLER_HPP
#define WINDOW_CONTROLLER_HPP

//#include <GLFW/glfw3.h>
//#include <cstdio>

#include <cstdint>
#include <any>
#include <string>

namespace OpenMIMO
{
    struct WindowProps
    {
        uint32_t Width;
        uint32_t Height;
        std::string Title;

        WindowProps(uint32_t width = 1280, uint32_t height = 720, std::string_view title = "OpenMIMO Plot") :
            Width(width), Height(height), Title(title)
        {}
    };

    class WindowController
    {
        friend class Application;
    public:

        virtual bool ShouldClose() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual std::any GetNativeWindow() const = 0;

        virtual void Update() = 0;

        virtual void Present() = 0;
    protected:
        virtual void ReceiveCloseEvent(bool shouldClose) = 0;
        virtual void ResetWindowDimensions(uint32_t width, uint32_t height) = 0;
    };
}
/*static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}*/

#endif