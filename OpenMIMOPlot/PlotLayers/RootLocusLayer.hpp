#ifndef ROOT_LOCUS_LAYER_HPP
#define ROOT_LOCUS_LAYER_HPP

#include "Core/Layer.hpp"
#include "Utils/PointCloud.hpp"
#include <OpenMIMO/RootLocusContainer.hpp>
#include <complex>

namespace OpenMIMO
{
    class RootLocusLayer : public Layer
    {
    private:
        RootLocusContainer<double> m_RootLocus;
        PointCloud<double> m_PlotPoints;

        void ImGUIRender();

        std::vector<double> m_Cast;

        void CastEigenToVector(const Eigen::Matrix<std::complex<double>, -1, 1>& vector);
    public:
        RootLocusLayer(const TransferFunction<double>& plant);
        ~RootLocusLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
    };
}

#endif
