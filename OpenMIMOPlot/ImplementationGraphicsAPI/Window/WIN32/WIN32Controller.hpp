#ifndef WIN32_CONTROLLER_HPP
#define WIN32_CONTROLLER_HPP

#include "InterfaceGraphicsAPI/WindowController.hpp"
#include "InterfaceGraphicsAPI/GraphicsContext.hpp"

#include <cstdio>
#include <string>
#include "Events/EventDispatcher.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace OpenMIMO
{
    struct WindowState
    {
        bool IsMinimized;
        EventDispatcher* Dispatcher;

        uint32_t Width;
        uint32_t Height;
        std::wstring Title;
    };

    class WIN32Controller : public WindowController
    {
    public:
        WIN32Controller(EventDispatcher* dispatcher, const WindowProps& props = WindowProps());
        ~WIN32Controller();

        virtual bool ShouldClose() const override;

        virtual uint32_t GetWidth() const override;
        virtual uint32_t GetHeight() const override;

        virtual std::any GetNativeWindow() const override;

        virtual void Update() override;

        virtual void Present() override;

    protected:

        virtual void ReceiveCloseEvent(bool shouldClose) override;
        virtual void ResetWindowDimensions(uint32_t width, uint32_t height) override;

    private:
        
        bool m_ShouldClose = false;

        WindowState m_WindowState;
        HWND m_Window;
        WNDCLASSEXW m_WindowClass;

        void GetStartupParams(HINSTANCE* hInstance, LPWSTR* nCmdLine, WORD* nCmdShow);
        void CreateWindowClass(WNDCLASSEXW* windowClass, HINSTANCE* instance);

        void CalculateWindowDimensionInitialization(LPRECT dimensions, long windowFlags, bool windowed);
    };
}

#endif