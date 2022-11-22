#include "TestLayer.hpp"
#include "imgui.h"
#include "implot.h"


OpenMIMO::TestLayer::TestLayer() :
    Layer("Test Layer")
{
    poles[0] = { -3,0 };
    poles[1] = { -5,2 };
    poles[2] = { -5,-2 };

    for (size_t i = 0; i < 3; i++)
    {
        real_poles[i] = poles[i].real();
        imag_poles[i] = poles[i].imag();
    }
}

OpenMIMO::TestLayer::~TestLayer(){}

void OpenMIMO::TestLayer::OnAttach()
{

}
void OpenMIMO::TestLayer::OnDetach(){}
void OpenMIMO::TestLayer::OnUpdate()
{
    ImGUIRender();
}

void OpenMIMO::TestLayer::ImGUIRender()
{
    //Only for tests will be removed from here
    ImPlot::ShowDemoWindow();
    ImPlot::ShowStyleEditor();

    ImGui::Begin("My Window");
    if (ImPlot::BeginPlot("My Plot")) {
        ImPlot::SetupAxesLimits(8,-8,-4.5,4.5);
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 1.0f);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
        ImPlot::PlotScatter<double>("Data 1", real_poles, imag_poles, 3);
        ImPlot::PopStyleVar();
        ImPlot::EndPlot();
    }
    ImGui::End();
}
