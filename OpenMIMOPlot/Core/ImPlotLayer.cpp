#include "ImPlotLayer.hpp"
#include "implot.h"

OpenMIMO::ImPlotLayer::ImPlotLayer(std::string_view layerName) :
    Layer(layerName)
{}

OpenMIMO::ImPlotLayer::~ImPlotLayer()
{}

void OpenMIMO::ImPlotLayer::OnAttach()
{
    ImPlot::CreateContext();
}

void OpenMIMO::ImPlotLayer::OnDetach()
{
    ImPlot::DestroyContext();
}

void OpenMIMO::ImPlotLayer::OnUpdate()
{

}
