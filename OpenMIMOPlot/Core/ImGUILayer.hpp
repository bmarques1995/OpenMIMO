#ifndef IMGUI_LAYER_HPP
#define IMGUI_LAYER_HPP

#include "Layer.hpp"

class ImGUILayer : public Layer
{
private:
public:
    ImGUILayer(std::string_view layerName = "ImGUIDebugLayer");
    ~ImGUILayer();

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
};

#endif
