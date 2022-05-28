#include "GraphicsInjector.hpp"

#include "ImplementationGraphicsAPI/ImGUI/GLFWGL4/GLFWGL4ImGUILayer.hpp"
#include "ImplementationGraphicsAPI/Window/GLFW/GLFWController.hpp"
#include "ImplementationGraphicsAPI/Graphics/GL4/GL4Context.hpp"

#ifdef WINDOWS_PLOT

#include "ImplementationGraphicsAPI/ImGUI/WIN32D3D11/WIN32D3D11ImGUILayer.hpp"
#include "ImplementationGraphicsAPI/Window/WIN32/WIN32Controller.hpp"
#include "ImplementationGraphicsAPI/Graphics/D3D11/D3D11Context.hpp"

#endif

#include <iostream>

using std::cout;

GraphicsInjector::GraphicsInjector()
{
    std::string_view currentGraphicsPair;

    //Register All API combinations in this constructor

    currentGraphicsPair = "GLFW" "GL4";
    m_FunctionMap[currentGraphicsPair] = [](const WindowProps& props) -> GraphicsStartup
    {
        WindowController* controller = new GLFWController(props);
        GraphicsContext* context = new GL4Context(controller);
        ImGUILayer* layer = new GLFWGL4ImGUILayer(std::any_cast<GLFWwindow*>(controller->GetNativeWindow()));
        GraphicsStartup startup(controller, context, layer);
        return startup;
    };

#ifdef WINDOWS_PLOT
    currentGraphicsPair = "WIN32" "D3D11";

    m_FunctionMap[currentGraphicsPair] = [](const WindowProps& props) -> GraphicsStartup
    {
        WindowController* controller = new WIN32Controller(props);
        GraphicsContext* context = new D3D11Context(controller);
        GraphicsMinimal graphicsDevice = std::any_cast<GraphicsMinimal>(context->GetComponentConstructor());
        ImGUILayer* layer = new WIN32D3D11ImGUILayer(std::any_cast<HWND>(controller->GetNativeWindow()),graphicsDevice.Device, graphicsDevice.DeviceContext);
        GraphicsStartup startup(controller, context, layer);
        return startup;
    };
#endif // Register Windows Ony APIs

    
}

GraphicsInjector::~GraphicsInjector()
{

}

GraphicsStartup GraphicsInjector::GetGraphics(const std::pair<std::string_view, std::string_view>& map, const WindowProps props)
{
    std::string pairName;
    ProcessGraphicsPair(map, &pairName);
    std::string_view pair = pairName;
    if (m_FunctionMap.find(pair) != m_FunctionMap.end())
        return m_FunctionMap[pair](props);
    else
        return GraphicsStartup(nullptr, nullptr, nullptr);
}

void GraphicsInjector::ProcessGraphicsPair(const std::pair<std::string_view, std::string_view>& map, std::string* returnType)
{
    std::stringstream pairInput;
    pairInput << map.first << map.second;
    *returnType = pairInput.str();
}
