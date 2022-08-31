#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <Eigen/Dense>
#include <iostream>
#include <list>

namespace OpenMIMO
{
    template<typename T>
    class Polynomial
    {
    public:
        Polynomial(std::list<T> elements);
        Polynomial();
        ~Polynomial() = default;

        Polynomial operator+(Polynomial& p1);
        Polynomial operator-(Polynomial& p1);
        Polynomial operator*(Polynomial& p1);
        void operator+=(Polynomial& p1);
        void operator-=(Polynomial& p1);
        void operator*=(Polynomial& p1);

        const Eigen::Matrix<T, -1, 1>& GetPolynomial() const;

    private:
        Eigen::Matrix<T, -1, 1> m_Polynomial;
        bool m_PolynomialLinear;
    };

}

#include "Polynomial.inl"

#endif
