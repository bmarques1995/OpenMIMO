#ifndef TRANSFER_FUNCTION_HPP
#define TRANSFER_FUNCTION_HPP

#include "Polynomial.hpp"
#include <utility>
#include <initializer_list>
#include "utils/ComplexSortClassifier.hpp"
#include <iostream>

using Eigen::internal::pointer_based_stl_iterator;

namespace OpenMIMO
{
	

	template<typename T>
	class TransferFunction
	{
	public:
		TransferFunction(std::initializer_list<T> numerator, std::initializer_list<T> denominator);
		TransferFunction();
		
		~TransferFunction() = default;

		TransferFunction operator+(TransferFunction& t1);
		TransferFunction operator-(TransferFunction& t1);
		TransferFunction operator*(TransferFunction& t1);
		void operator+=(TransferFunction& t1);
		void operator-=(TransferFunction& t1);
		void operator*=(TransferFunction& t1);
		void operator=(const std::pair<std::initializer_list<T>, std::initializer_list<T>>& numeratorAndDenominator);
		
		bool IsApproximated(const TransferFunction& tf2);

		const Eigen::Matrix<T, -1, 1>& GetNumerator() const;
		const Eigen::Matrix<T, -1, 1>& GetDenominator() const;
	private:
		Polynomial<T> m_Numerator;
		Polynomial<T> m_Denominator;

		void Reset();
		void ResetWithGain();
		void FilterRoots(Eigen::Matrix<std::complex<T>, -1, 1>& roots);

		void Simplify();
	};
}

#include "TransferFunction.inl"

#endif
