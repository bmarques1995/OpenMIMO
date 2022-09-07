#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <Eigen/Dense>
#include <iostream>
#include <algorithm>
#include <list>
#include "utils/ComplexSortClassifier.hpp"
#include "utils/Sort.hpp"

using Eigen::internal::pointer_based_stl_iterator;

namespace OpenMIMO
{
    template<typename T>
    class Polynomial
    {
    public:
        Polynomial(const std::initializer_list<T>& elements, T tolerance);
        Polynomial();
        ~Polynomial() = default;

        Polynomial operator+(Polynomial& p1);
        Polynomial operator-(Polynomial& p1);
        Polynomial operator*(Polynomial& p1);
        void operator+=(Polynomial& p1);
        void operator-=(Polynomial& p1);
        void operator*=(Polynomial& p1);
        void operator=(const std::initializer_list<T>& elements);

        const Eigen::Matrix<T, -1, 1>& GetPolynomial() const;
        const size_t GetPolynomialSize() const;
        Eigen::Matrix<std::complex<T>, -1, 1> GetRoots() const;

        void InsertRoot(pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& root, const pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& end);

    private:

        void InsertRealRoot(const std::complex<T>& root);
        void InsertComplexRoot(pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& root, const pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& end);

        void InitializePolynomial(const std::initializer_list<T>& elements);

        Eigen::Matrix<T, -1, 1> m_Polynomial;
        T m_Tolerance;
        bool m_PolynomialLinear;
    };

}

#include "Polynomial.inl"

#endif
