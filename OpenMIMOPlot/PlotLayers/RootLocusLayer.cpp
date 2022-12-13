#include "RootLocusLayer.hpp"
#include "imgui.h"
#include "implot.h"

void OpenMIMO::RootLocusLayer::ImGUIRender()
{
    ImGui::Begin("Root Locus");
    if (ImGui::BeginTabBar("Surface")) {
        if (ImGui::BeginTabItem("Position")) {
            if (ImPlot::BeginPlot("My Plot")) {
                ImPlot::SetupAxesLimits(8, -8, -4.5, 4.5);
				for (size_t i = 0; i < m_PlotPoints.GetNumberOfRows(); i++)
				{
					ImPlot::PlotLine<double>("Data 1", m_PlotPoints.GetColumn(2*i).data(), m_PlotPoints.GetColumn(2*i+1).data(), m_PlotPoints.GetColumn(0).size());
				}
                
				ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
				ImPlot::PushStyleVar(ImPlotStyleVar_PlotDefaultSize, ImVec2(800, 450));
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

OpenMIMO::RootLocusLayer::RootLocusLayer(const TransferFunction<double>& plant) :
	m_RootLocus(plant)
{
	size_t numberOfRoots = (size_t)m_RootLocus.GetRootLocus(0).rows();
	m_PlotPoints.Start(numberOfRoots, 2);
	m_Cast.resize(numberOfRoots * 2);
	
	for (size_t i = 0; i < 600000; i++)
	{
		CastEigenToVector(m_RootLocus.GetRootLocus(i*.01));
		m_PlotPoints.PushRow(m_Cast);
	}
}

OpenMIMO::RootLocusLayer::~RootLocusLayer()
{
}

void OpenMIMO::RootLocusLayer::CastEigenToVector(const Eigen::Matrix<std::complex<double>, -1, 1>& vector)
{
	for (size_t i = 0; i < (size_t)vector.rows(); i++)
	{
		m_Cast[2 * i] = vector[i].real();
		m_Cast[2 * i + 1] = vector[i].imag();
	}
}

void OpenMIMO::RootLocusLayer::OnAttach()
{
}

void OpenMIMO::RootLocusLayer::OnDetach()
{
}

void OpenMIMO::RootLocusLayer::OnUpdate()
{
	ImGUIRender();
}
