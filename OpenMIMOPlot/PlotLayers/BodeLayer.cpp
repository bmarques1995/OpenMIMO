#include "BodeLayer.hpp"
#include "imgui.h"
#include "implot.h"

void OpenMIMO::BodeLayer::ImGUIRender()
{
    ImGui::Begin("Bode Diagram");
    if (ImGui::BeginTabBar("Diagrams")) {
        if (ImGui::BeginTabItem("Magnitude")) {
            if (ImPlot::BeginPlot("Module")) {
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);
                ImPlot::SetupAxesLimits(0.1, 100, 2, -80);
                ImPlot::PlotLine<double>("Data 1", m_PlotPoints.GetColumn(0).data(), m_PlotPoints.GetColumn(1).data(), m_PlotPoints.GetColumn(0).size());
                ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
                ImPlot::PushStyleVar(ImPlotStyleVar_PlotDefaultSize, ImVec2(800, 450));
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
                ImPlot::PopStyleVar();
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Phase")) {
            if (ImPlot::BeginPlot("Angle")) {
                ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Log10);
                ImPlot::SetupAxesLimits(0.1, 100, 90, -180);
                ImPlot::PlotLine<double>("Data 1", m_PlotPoints.GetColumn(0).data(), m_PlotPoints.GetColumn(2).data(), m_PlotPoints.GetColumn(0).size());
                ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
                ImPlot::PushStyleVar(ImPlotStyleVar_PlotDefaultSize, ImVec2(800, 450));
                ImPlot::SetNextMarkerStyle(ImPlotMarker_Cross, 6, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(25));
                ImPlot::PopStyleVar();
                ImPlot::EndPlot();
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
}

void OpenMIMO::BodeLayer::CastBodeToVector(const std::complex<double>& bode, double frequency)
{
    m_Cast[0] = frequency;
    m_Cast[1] = bode.real();
    m_Cast[2] = (bode.imag())*180/acos(-1);
}

OpenMIMO::BodeLayer::BodeLayer(const TransferFunction<double>& plant) :
    m_Bode(plant)
{
    m_PlotPoints.Start(1, 3);
    m_Cast.resize(3);

    for (size_t i = 0; i < 60000; i++)
    {
        CastBodeToVector(m_Bode.GetBodeValues(i*.01),i*.01);
        m_PlotPoints.PushRow(m_Cast);
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
