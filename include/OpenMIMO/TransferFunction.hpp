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
		TransferFunction operator*(T gain);
		void operator+=(TransferFunction& t1);
		void operator-=(TransferFunction& t1);
		void operator*=(TransferFunction& t1);
		void operator*=(T gain);
		void operator=(const std::pair<std::initializer_list<T>, std::initializer_list<T>>& numeratorAndDenominator);
		
		bool IsApproximated(const TransferFunction& tf2);

		const Polynomial<T>& GetNumerator() const;
		const Polynomial<T>& GetDenominator() const;
		T GetFinalValue() const;

		static void FilterRoots(Eigen::Matrix<std::complex<T>, -1, 1>& roots);

	private:
		Polynomial<T> m_Numerator;
		Polynomial<T> m_Denominator;

		void Reset();
		void ResetWithGain();
		

		void Simplify();
	};
}

#include "TransferFunction.inl"

#endif
