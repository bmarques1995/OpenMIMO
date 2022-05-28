#ifndef LAYER_HPP
#define LAYER_HPP

#include <string>

namespace OpenMIMO
{
    class Layer
    {
    protected:
        std::string_view m_LayerName;
    public:
        Layer(std::string_view layerName = "DebugLayer");
        virtual ~Layer();

        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnUpdate() = 0;
        virtual std::string_view GetName() const;
    };
}

#endif
