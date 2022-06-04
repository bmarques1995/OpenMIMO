#include "WIN32Controller.hpp"
#include "backends/imgui_impl_win32.h"
#include <tchar.h>
#include <cassert>
#include "Events/ApplicationEvent.hpp"

OpenMIMO::WIN32Controller::WIN32Controller(EventDispatcher* dispatcher, const WindowProps& props)
{
    m_WindowState.Width = props.Width;
    m_WindowState.Height = props.Height;
    m_WindowState.Title = std::wstring(props.Title.begin(), props.Title.end());
    m_WindowState.Dispatcher = dispatcher;
    m_WindowState.IsMinimized = false;
    
    HINSTANCE hInstance;
    LPWSTR cmdLine;
    WORD cmdShow;
    RECT windowDimensions;

    GetStartupParams(&hInstance, &cmdLine, &cmdShow);
    CreateWindowClass(&m_WindowClass, &hInstance);
    
    
    DWORD windowedFlags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION | WS_MAXIMIZEBOX | WS_THICKFRAME;
    DWORD popupFlags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP;

    CalculateWindowDimensionInitialization(&windowDimensions, windowedFlags, true);

    RegisterClassExW(&m_WindowClass);

    m_Window = CreateWindowExW
    (
        0,
        m_WindowState.Title.c_str(),
        m_WindowState.Title.c_str(),
        windowedFlags,
        100,
        100,
        windowDimensions.right - windowDimensions.left,
        windowDimensions.bottom - windowDimensions.top,
        nullptr,
        nullptr,
        m_WindowClass.hInstance,
        nullptr
    );

    SetWindowLongPtrW(m_Window, 0, (LONG_PTR)&m_WindowState);

    ShowWindow(m_Window, cmdShow);
    UpdateWindow(m_Window);
}

OpenMIMO::WIN32Controller::~WIN32Controller()
{
    DestroyWindow(m_Window);
    m_WindowState.Dispatcher = nullptr;
}

bool OpenMIMO::WIN32Controller::ShouldClose() const
{
    return m_ShouldClose;
}

uint32_t OpenMIMO::WIN32Controller::GetWidth() const
{
    return m_WindowState.Width;
}

uint32_t OpenMIMO::WIN32Controller::GetHeight() const
{
    return m_WindowState.Height;
}

std::any OpenMIMO::WIN32Controller::GetNativeWindow() const
{
    return m_Window;
}

void OpenMIMO::WIN32Controller::Update()
{
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
        if (msg.message == WM_QUIT)
            m_ShouldClose = true;
    }
}

void OpenMIMO::WIN32Controller::Present()
{
    
}

void OpenMIMO::WIN32Controller::ReceiveCloseEvent(bool shouldClose)
{
    m_ShouldClose = shouldClose;
}

void OpenMIMO::WIN32Controller::ResetWindowDimensions(uint32_t width, uint32_t height)
{
    m_WindowState.Width = width;
    m_WindowState.Height = height;
}

void OpenMIMO::WIN32Controller::GetStartupParams(HINSTANCE* hInstance, LPWSTR* lpCmdLine, WORD* nCmdShow)
{
    *hInstance = GetModuleHandleW(NULL);
    *lpCmdLine = GetCommandLineW();
    STARTUPINFO si;
    GetStartupInfo(&si);
    *nCmdShow = SW_SHOWDEFAULT;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OpenMIMO::WIN32Controller::CreateWindowClass(WNDCLASSEXW* windowClass, HINSTANCE* instance)
{
    ZeroMemory(windowClass, sizeof(*windowClass));
    windowClass->hInstance = *instance;
    windowClass->cbSize = sizeof(*windowClass);
    windowClass->cbClsExtra = 0;
    windowClass->cbWndExtra = sizeof(void*);
    windowClass->style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    windowClass->hIcon = nullptr;
    windowClass->hCursor = LoadCursor(*instance, MAKEINTRESOURCE(230));
    windowClass->hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    windowClass->lpszMenuName = nullptr;
    windowClass->lpszClassName = m_WindowState.Title.c_str();

    windowClass->lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        WindowState* state = reinterpret_cast<WindowState*>(GetWindowLongPtrW(hWnd, 0));
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;
        switch (msg)
        {
            case WM_SYSCOMMAND:
                if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                    return 0;
                break;
            case WM_SIZE:
            {
                const uint32_t width = LOWORD(lParam);
                const uint32_t height = HIWORD(lParam);
                const bool isMinimized = wParam == SIZE_MINIMIZED;
                
                if (state->IsMinimized == isMinimized)
                {
                    WindowMinimizeEvent e(isMinimized);
                    state->Dispatcher->Dispatch(e);
                }

                if ((width != state->Width) || (height != state->Height))
                {
                    {
                        WindowResizeEvent e(width, height);
                        state->Dispatcher->Dispatch(e);
                    }
                    {
                        FramebufferResizeEvent e(width, height);
                        state->Dispatcher->Dispatch(e);
                    }
                }

                break;
            }
            case WM_SIZING:
            {
                break;
            }
            case WM_CLOSE:
            case WM_QUIT:
            {
                WindowCloseEvent e;
                state->Dispatcher->Dispatch(e);
                break; 
            }
        }
        return ::DefWindowProcW(hWnd, msg, wParam, lParam);
    };
}

void OpenMIMO::WIN32Controller::CalculateWindowDimensionInitialization(LPRECT dimensions, long windowFlags, bool windowed)
{
    if (!windowed)
    {
        DEVMODEW dm;
        ZeroMemory(&dm, sizeof(dm));
        dm.dmSize = sizeof(dm);

        EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &dm);

        m_WindowState.Width = dm.dmPelsWidth;
        m_WindowState.Height = dm.dmPelsHeight;
    }
    *dimensions = { 0, 0, (LONG)m_WindowState.Width, (LONG)m_WindowState.Height };
    AdjustWindowRectEx(dimensions, windowFlags, 0, 0);
}
