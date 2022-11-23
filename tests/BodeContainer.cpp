#include <gtest/gtest.h>
#include <OpenMIMO/BodeContainer.hpp>
#include <iostream>

namespace OpenMIMO
{
    TEST(BodeContainer, BodeValues)
    {   
        TransferFunction<double> system({ 1 }, { 1, 6, 5 });
        BodeContainer bContainer(system);
        auto bodeValue = bContainer.GetBodeValues(1.0);
        std::complex<double> expectedBodeValue(-17.160033436347990, -0.982793723247329);
        ASSERT_TRUE(FloatOperator::ComplexIsApprox(bodeValue, expectedBodeValue, 1e-5));
    }
}