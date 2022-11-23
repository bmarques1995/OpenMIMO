#ifndef GRAPHICS_INJECTOR_HPP
#define GRAPHICS_INJECTOR_HPP

#include <functional>
#include <unordered_map>

#include "ImGUILayer.hpp"
#include "InterfaceGraphicsAPI/WindowController.hpp"
#include "InterfaceGraphicsAPI/GraphicsContext.hpp"
#include "Events/EventDispatcher.hpp"

namespace OpenMIMO
{
#pragma region Structure

    struct GraphicsStartup
    {
        ImGUILayer* Layer;
        WindowController* Controller;
        GraphicsContext* Context;

        GraphicsStartup() {}

        GraphicsStartup(WindowController* controller, GraphicsContext* context, ImGUILayer* layer) :
            Layer(layer), Controller(controller), Context(context)
        {}
    };

#pragma endregion

    class GraphicsInjector
    {
    private:
        std::unordered_map<std::string_view, std::function<GraphicsStartup(EventDispatcher*, const WindowProps&)>> m_FunctionMap;

        void ProcessGraphicsPair(const std::pair<std::string, std::string>& map, std::string* returnType);
    public:
        GraphicsInjector();
        ~GraphicsInjector();

        GraphicsStartup GetGraphics(const std::pair<std::string, std::string>& map, EventDispatcher* dispatcher, const WindowProps props = WindowProps());
    };

}

#endif
