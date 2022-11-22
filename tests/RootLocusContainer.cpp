#include <gtest/gtest.h>
#include <OpenMIMO/RootLocusContainer.hpp>
#include <iostream>

namespace OpenMIMO
{
    TEST(RootLocusContainer, RootLocus)
    {
        TransferFunction<double> system({ 1 }, { 1, 6, 5 });
        RootLocusContainer<double> rLocusContainer(system);
        Eigen::VectorXcd rootLocus = rLocusContainer.GetRootLocus(3);
        Eigen::VectorXcd expectedRootLocus;
        expectedRootLocus.resize(2);
        expectedRootLocus(0) = std::complex(-2.0f, 0.0f);
        expectedRootLocus(1) = std::complex(-4.0f, 0.0f);
        ASSERT_TRUE(rootLocus.isApprox(expectedRootLocus));
    }
}