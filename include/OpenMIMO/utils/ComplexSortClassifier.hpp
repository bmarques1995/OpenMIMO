#ifndef COMPLEX_SORT_CLASSIFIER_HPP
#define COMPLEX_SORT_CLASSIFIER_HPP

#include <complex>

namespace OpenMIMO
{
    namespace FloatOperator
    {
        template<typename T>
        bool IsApprox(T first, T second, T variation);
        template<>
        bool IsApprox<double>(double first, double second, double variation);
        template<>
        bool IsApprox<float>(float first, float second, float variation);
        template<typename T>
        bool IsGreater(T first, T second, T variation);
        template<>
        bool IsGreater<double>(double first, double second, double variation);
        template<>
        bool IsGreater<float>(float first, float second, float variation);
        template<typename T>
        bool IsLess(T first, T second, T variation);
        template<>
        bool IsLess<double>(double first, double second, double variation);
        template<>
        bool IsLess<float>(float first, float second, float variation);
        template<typename T>
        bool IsGreaterApprox(T first, T second, T variation);
        template<>
        bool IsGreaterApprox<double>(double first, double second, double variation);
        template<>
        bool IsGreaterApprox<float>(float first, float second, float variation);
        template<typename T>
        bool IsLessApprox(T first, T second, T variation);
        template<>
        bool IsLessApprox<double>(double first, double second, double variation);
        template<>
        bool IsLessApprox<float>(float first, float second, float variation);


        template<typename T>
        bool ComplexIsApprox(std::complex<T> first, std::complex<T> second, T variation);
        template<>
        bool ComplexIsApprox<double>(std::complex<double> first, std::complex<double> second, double variation);
        template<>
        bool ComplexIsApprox<float>(std::complex<float> first, std::complex<float> second, float variation);
        template<typename T>
        bool ComplexIsGreater(std::complex<T> first, std::complex<T> second, T variation);
        template<>
        bool ComplexIsGreater<double>(std::complex<double> first, std::complex<double> second, double variation);
        template<>
        bool ComplexIsGreater<float>(std::complex<float> first, std::complex<float> second, float variation);
        template<typename T>
        bool ComplexIsLess(std::complex<T> first, std::complex<T> second, T variation);
        template<>
        bool ComplexIsLess<double>(std::complex<double> first, std::complex<double> second, double variation);
        template<>
        bool ComplexIsLess<float>(std::complex<float> first, std::complex<float> second, float variation);
        template<typename T>
        bool ComplexIsGreaterApprox(std::complex<T> first, std::complex<T> second, T variation);
        template<>
        bool ComplexIsGreaterApprox<double>(std::complex<double> first, std::complex<double> second, double variation);
        template<>
        bool ComplexIsGreaterApprox<float>(std::complex<float> first, std::complex<float> second, float variation);
        template<typename T>
        bool ComplexIsLessApprox(std::complex<T> first, std::complex<T> second, T variation);
        template<>
        bool ComplexIsLessApprox<double>(std::complex<double> first, std::complex<double> second, double variation);
        template<>
        bool ComplexIsLessApprox<float>(std::complex<float> first, std::complex<float> second, float variation);
    }
}
#include "ComplexSortClassifier.inl"

#endif