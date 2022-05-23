#include "ImPlotLayer.hpp"
#include "implot.h"

ImPlotLayer::ImPlotLayer(std::string_view layerName) :
    Layer(layerName)
{}

ImPlotLayer::~ImPlotLayer()
{}

void ImPlotLayer::OnAttach()
{
    ImPlot::CreateContext();
}

void ImPlotLayer::OnDetach()
{
    ImPlot::DestroyContext();
}

void ImPlotLayer::OnUpdate()
{

}
