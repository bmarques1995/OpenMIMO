#include "WIN32Controller.hpp"
#include "backends/imgui_impl_win32.h"
#include <tchar.h>
#include <cassert>

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
    windowClass->hbrBackground = CreateSolidBrush(RGB(0,0,0));
    windowClass->lpszMenuName = nullptr;
    windowClass->lpszClassName = m_Title.c_str();

    windowClass->lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;
        switch (msg)
        {
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
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

        m_Width = dm.dmPelsWidth;
        m_Height = dm.dmPelsHeight;
    }
    *dimensions = { 0, 0, (LONG)m_Width, (LONG)m_Height };
    AdjustWindowRectEx(dimensions, windowFlags, 0, 0);
}

OpenMIMO::WIN32Controller::WIN32Controller(const WindowProps& props)
{
    m_Width = props.Width;
    m_Height = props.Height;
    m_Title = std::wstring(props.Title.begin(), props.Title.end());
    
    
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
        m_Title.c_str(),
        m_Title.c_str(),
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

    ShowWindow(m_Window, cmdShow);
    UpdateWindow(m_Window);
}

OpenMIMO::WIN32Controller::~WIN32Controller()
{
    DestroyWindow(m_Window);
}

bool OpenMIMO::WIN32Controller::ShouldClose() const
{
    return m_ShouldClose;
}

uint32_t OpenMIMO::WIN32Controller::GetWidth() const
{
    return m_Width;
}

uint32_t OpenMIMO::WIN32Controller::GetHeight() const
{
    return m_Height;
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
