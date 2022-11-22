#include "BodeLayer.hpp"
#include "imgui.h"
#include "implot.h"

void OpenMIMO::BodeLayer::ImGUIRender()
{
    ImGui::Begin("Bode Diagram");
    if (ImGui::BeginTabBar("Diagrams")) {
        if (ImGui::BeginTabItem("Magnitude")) {
            if (ImPlot::BeginPlot("My Plot")) {
                ImPlot::SetupAxesLimits(8, -8, -4.5, 4.5);
                ImPlot::PlotScatter<double>("Data 1", real_poles, imag_poles, 3);
                ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
                ImPlot::PopStyleVar();
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Phase")) {
            if (ImPlot::BeginPlot("My Plot")) {
                ImPlot::SetupAxesLimits(8, -8, -4.5, 4.5);
                ImPlot::PlotLine<double>("Data 1", real_poles, imag_poles, 3);
                ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
                ImPlot::PopStyleVar();
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

OpenMIMO::BodeLayer::BodeLayer()
{
    std::complex<double> poles[3];
    poles[0] = { -3,0 };
    poles[1] = { -5,7 };
    poles[2] = { -5,-7 };

    for (size_t i = 0; i < 3; i++)
    {
        real_poles[i] = poles[i].real();
        imag_poles[i] = poles[i].imag();
    }
}

OpenMIMO::BodeLayer::~BodeLayer()
{
}

void OpenMIMO::BodeLayer::OnAttach()
{
}

void OpenMIMO::BodeLayer::OnDetach()
{
}

void OpenMIMO::BodeLayer::OnUpdate()
{
	ImGUIRender();
}
