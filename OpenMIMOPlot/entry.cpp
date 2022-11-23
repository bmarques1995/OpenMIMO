#include "AppContainer.hpp"

#ifdef WINDOWS_PLOT

#include <windows.h>

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    OpenMIMO::Application* app = new OpenMIMO::AppContainer();
    app->Run();
    delete app;

    return 0;
}

#else

int main(int argc, char** argv)
{
    OpenMIMO::Application* app = new OpenMIMO::AppContainer();
    app->Run();
    delete app;

    return 0;
}

#endif // WINDOWS_PLOT
