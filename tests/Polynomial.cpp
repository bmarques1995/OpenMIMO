#include <gtest/gtest.h>
#include <OpenMIMO/Polynomial.hpp>
#include <iostream>

namespace OpenMIMO
{
    TEST(Polynomial, PolynomialAddingGreater)
    {
        OpenMIMO::Polynomial<double> p;
        OpenMIMO::Polynomial<double> p2({ 4, 7 }, 1E-6);
        p = { 1,5,6 };
        p += p2;
        Eigen::VectorXd compare;
        compare.resize(3);
        compare << 13.0, 9.0, 1.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }

    TEST(Polynomial, PolynomialAddingMinor)
    {
        OpenMIMO::Polynomial<double> p({ 1, 5, 6 },1E-6);
        OpenMIMO::Polynomial<double> p2({ 2, 6, 4, 7 }, 1E-6);
        p += p2;
        Eigen::VectorXd compare;
        compare.resize(4);
        compare << 13.0, 9.0, 7.0, 2.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }

    TEST(Polynomial, PolynomialSubtractingGreater)
    {
        OpenMIMO::Polynomial<double> p({ 1, 5, 6 }, 1E-6);
        OpenMIMO::Polynomial<double> p2({ 4, 7 }, 1E-6);
        p -= p2;
        Eigen::VectorXd compare;
        compare.resize(3);
        compare << -1.0, 1.0, 1.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }

    TEST(Polynomial, PolynomialSubtractingMinor)
    {
        OpenMIMO::Polynomial<double> p({ 1, 5, 6 }, 1E-6);
        OpenMIMO::Polynomial<double> p2({ 2, 6, 4, 7 }, 1E-6);
        p -= p2;
        Eigen::VectorXd compare;
        compare.resize(4);
        compare << -1.0, 1.0, -5.0, -2.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }

    TEST(Polynomial, PolynomialMultiply)
    {
        OpenMIMO::Polynomial<double> p({ 1, 5, 6 }, 1E-6);
        OpenMIMO::Polynomial<double> p2({ 1, 5 }, 1E-6);
        p *= p2;
        Eigen::VectorXd compare;
        compare.resize(4);
        compare << 30.0, 31.0, 10.0, 1.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }

    TEST(Polynomial, RealRoots)
    {
        OpenMIMO::Polynomial<double> p;
        p = { 1, 5, 6 };
        Eigen::VectorXcd expectedRoots;
        Eigen::VectorXcd currentRoots = p.GetRoots();
        expectedRoots.resize(2);
        expectedRoots(0) = std::complex(-3.0f, 0.0f);
        expectedRoots(1) = std::complex(-2.0f, 0.0f);
        OpenMIMO::Sorter::Sort(expectedRoots.begin(), expectedRoots.end(), OpenMIMO::FloatOperator::ComplexIsLess<double>, (size_t)expectedRoots.size());
        ASSERT_TRUE(expectedRoots.isApprox(currentRoots));
    }

    TEST(Polynomial, ComplexRoots)
    {
        OpenMIMO::Polynomial<double> p;
        OpenMIMO::Polynomial<double> p2({ 4, 7 }, 1E-6);
        p = { 1,5,6 };
        p += p2;
        Eigen::VectorXd compare;
        compare.resize(3);
        compare << 13.0, 9.0, 1.0;
        ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
    }
}