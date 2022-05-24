#include "GraphicsInjector.hpp"

#include "ImplementationGraphicsAPI/ImGUI/GLFWGL4/GLFWGL4ImGUILayer.hpp"
#include "ImplementationGraphicsAPI/Window/GLFW/GLFWController.hpp"
#include "ImplementationGraphicsAPI/Graphics/GL4/GL4Context.hpp"

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
}

GraphicsInjector::~GraphicsInjector()
{

}

GraphicsStartup GraphicsInjector::GetGraphics(const std::pair<std::string_view, std::string_view>& map, const WindowProps props)
{
    std::string pairName;
    ProcessGraphicsPair(map, &pairName);
    std::string_view pair = pairName;
    return m_FunctionMap[pair](props);
}

void GraphicsInjector::ProcessGraphicsPair(const std::pair<std::string_view, std::string_view>& map, std::string* returnType)
{
    std::stringstream pairInput;
    pairInput << map.first << map.second;
    *returnType = pairInput.str();
}
