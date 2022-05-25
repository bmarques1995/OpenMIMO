#include "TestLayer.hpp"
#include "imgui.h"
#include "implot.h"


TestLayer::TestLayer() :
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

TestLayer::~TestLayer(){}

void TestLayer::OnAttach()
{

}
void TestLayer::OnDetach(){}
void TestLayer::OnUpdate()
{
    ImGUIRender();
}

void TestLayer::ImGUIRender()
{
    //Only for tests will be removed from here
    ImPlot::ShowStyleEditor();

    ImGui::Begin("My Window");
    if (ImPlot::BeginPlot("My Plot")) {
        ImPlot::SetupAxesLimits(8,-8,-4.5,4.5);
        ImPlot::PlotScatter<double>("Data 1", real_poles, imag_poles, 3);
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
        ImPlot::PopStyleVar();
        ImPlot::EndPlot();
    }
    ImGui::End();
}