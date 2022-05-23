#ifndef IMPLOT_LAYER_HPP
#define IMPLOT_LAYER_HPP

#include "Layer.hpp"

class ImPlotLayer : public Layer
{
private:
    
public:
    ImPlotLayer(std::string_view layerName = "ImPlotDebugLayer");
    ~ImPlotLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
};

#endif
