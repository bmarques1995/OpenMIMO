#include <gtest/gtest.h>
#include <OpenMIMO/Polynomial.hpp>
#include <iostream>

TEST(Polynomial, PolynomialAddingGreater)
{
    std::list<double> input;
    input.push_back(1);
    input.push_back(5);
    input.push_back(6);
    OpenMIMO::Polynomial<double> p(input);
    input.clear();
    input.push_back(4);
    input.push_back(7);
    OpenMIMO::Polynomial<double> p2(input);
    p += p2;
    Eigen::VectorXd compare;
    compare.resize(3);
    compare << 13.0, 9.0, 1.0;
    ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
}

TEST(Polynomial, PolynomialAddingMinor)
{
    std::list<double> input;
    input.push_back(1);
    input.push_back(5);
    input.push_back(6);
    OpenMIMO::Polynomial<double> p(input);
    input.clear();
    input.push_back(2);
    input.push_back(6);
    input.push_back(4);
    input.push_back(7);
    OpenMIMO::Polynomial<double> p2(input);
    p += p2;
    Eigen::VectorXd compare;
    compare.resize(4);
    compare << 13.0, 9.0, 7.0, 2.0;
    ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
}

TEST(Polynomial, PolynomialSubtractingGreater)
{
    std::list<double> input;
    input.push_back(1);
    input.push_back(5);
    input.push_back(6);
    OpenMIMO::Polynomial<double> p(input);
    input.clear();
    input.push_back(4);
    input.push_back(7);
    OpenMIMO::Polynomial<double> p2(input);
    p -= p2;
    Eigen::VectorXd compare;
    compare.resize(3);
    compare << -1.0, 1.0, 1.0;
    ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
}

TEST(Polynomial, PolynomialSubtractingMinor)
{
    std::list<double> input;
    input.push_back(1);
    input.push_back(5);
    input.push_back(6);
    OpenMIMO::Polynomial<double> p(input);
    input.clear();
    input.push_back(2);
    input.push_back(6);
    input.push_back(4);
    input.push_back(7);
    OpenMIMO::Polynomial<double> p2(input);
    p -= p2;
    Eigen::VectorXd compare;
    compare.resize(4);
    compare << -1.0, 1.0, -5.0, -2.0;
    ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
}

TEST(Polynomial, PolynomialMultiply)
{
    std::list<double> input;
    input.push_back(1);
    input.push_back(5);
    input.push_back(6);
    OpenMIMO::Polynomial<double> p(input);
    input.clear();
    input.push_back(1);
    input.push_back(5);
    OpenMIMO::Polynomial<double> p2(input);
    p *= p2;
    Eigen::VectorXd compare;
    compare.resize(4);
    compare << 30.0, 31.0, 10.0, 1.0;
    ASSERT_TRUE(compare.isApprox(p.GetPolynomial()));
}