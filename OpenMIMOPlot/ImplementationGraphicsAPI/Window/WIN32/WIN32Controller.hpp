#ifndef WIN32_CONTROLLER_HPP
#define WIN32_CONTROLLER_HPP

#include "InterfaceGraphicsAPI/WindowController.hpp"
#include "InterfaceGraphicsAPI/GraphicsContext.hpp"

#include <cstdio>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace OpenMIMO
{
    enum class CallbackResponses
    {
        ShouldClose = 0x1,
        Resized = 0x2
    };

    class WIN32Controller : public WindowController
    {
        friend class Application;
    private:
        //GLFWwindow* m_Window;
        uint32_t m_Width;
        uint32_t m_Height;
        std::wstring m_Title;
        bool m_ShouldClose = false;

        HWND m_Window;
        WNDCLASSEXW m_WindowClass;

        void GetStartupParams(HINSTANCE* hInstance, LPWSTR* nCmdLine, WORD* nCmdShow);
        void CreateWindowClass(WNDCLASSEXW* windowClass, HINSTANCE* instance);

        void CalculateWindowDimensionInitialization(LPRECT dimensions, long windowFlags, bool windowed);

    public:
        WIN32Controller(const WindowProps& props = WindowProps());
        ~WIN32Controller();

        virtual bool ShouldClose() const override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

        virtual std::any GetNativeWindow() const override;

        virtual void Update() override;

        virtual void Present() override;
    };
}

#endif