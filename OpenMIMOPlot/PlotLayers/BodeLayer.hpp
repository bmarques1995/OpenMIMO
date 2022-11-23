#ifndef BODE_LAYER_HPP
#define BODE_LAYER_HPP

#include "Core/Layer.hpp"
#include "Utils/PointCloud.hpp"
#include <complex>
#include <OpenMIMO/BodeContainer.hpp>


namespace OpenMIMO
{
    class BodeLayer : public Layer
    {
    private:
        BodeContainer<double> m_Bode;
        PointCloud<double> m_PlotPoints;

        void ImGUIRender();

        std::vector<double> m_Cast;

        void CastBodeToVector(const std::complex<double>& bode, double frequency);
    public:
        BodeLayer(const TransferFunction<double>& plant);
        ~BodeLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
    };
}

#endif
