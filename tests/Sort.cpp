#include <gtest/gtest.h>
#include <OpenMIMO/utils/Sort.hpp>
#include <OpenMIMO/utils/ComplexSortClassifier.hpp>
#include <Eigen/Dense>

#include <iostream>

namespace OpenMIMO
{
    TEST(Sort, LessFive)
    {
        Eigen::VectorXcd unsorted;
        unsorted.resize(4);
        unsorted(0) = std::complex<double>(-4,0);
        unsorted(1) = std::complex<double>(-2,0);
        unsorted(2) = std::complex<double>(-3,1);
        unsorted(3) = std::complex<double>(-3,-1);

        OpenMIMO::Sorter::Sort(unsorted.begin(), unsorted.end(), FloatOperator::ComplexIsLess<double>, (size_t) unsorted.size());

        Eigen::VectorXcd sorted;
        sorted.resize(4);
        sorted(0) = std::complex<double>(-4,0);
        sorted(1) = std::complex<double>(-3,-1);
        sorted(2) = std::complex<double>(-3,1);
        sorted(3) = std::complex<double>(-2,0);

        ASSERT_TRUE(sorted.isApprox(unsorted));
    }

    TEST(Sort, MoreFive)
    {
        Eigen::VectorXcd unsorted;
        unsorted.resize(8);
        unsorted(0) = std::complex<double>(-8,1);
        unsorted(1) = std::complex<double>(-6,0);
        unsorted(2) = std::complex<double>(-10,0);
        unsorted(3) = std::complex<double>(-5,1);
        unsorted(4) = std::complex<double>(-8,-1);
        unsorted(5) = std::complex<double>(3,0);
        unsorted(6) = std::complex<double>(-8,0);
        unsorted(7) = std::complex<double>(-5,-1);

        OpenMIMO::Sorter::Sort(unsorted.begin(), unsorted.end(), FloatOperator::ComplexIsLess<double>, (size_t) unsorted.size());

        Eigen::VectorXcd sorted;
        sorted.resize(8);
        sorted(0) = std::complex<double>(-10,0);
        sorted(1) = std::complex<double>(-8,0);
        sorted(2) = std::complex<double>(-8,-1);
        sorted(3) = std::complex<double>(-8,1);
        sorted(4) = std::complex<double>(-6,0);
        sorted(5) = std::complex<double>(-5,-1);
        sorted(6) = std::complex<double>(-5,1);
        sorted(7) = std::complex<double>(3,0);

        ASSERT_TRUE(sorted.isApprox(unsorted));
    }
} // namespace OpenMIMO
