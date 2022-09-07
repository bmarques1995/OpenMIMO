#include <gtest/gtest.h>
#include <OpenMIMO/utils/ComplexSortClassifier.hpp>

namespace OpenMIMO
{
	TEST(Classifier, ComplexIsApprox)
	{
		std::complex<double> first = { 4.0, 1.3 };
		std::complex<double> second = { 4.000001, 1.2999991 };
		ASSERT_TRUE(FloatOperator::ComplexIsApprox(first, second, .0001));
	}

	TEST(Classifier, ComplexIsNotApprox)
	{
		std::complex<double> first = { 4.0, 1.2 };
		std::complex<double> second = { 4.000001, 1.2999991 };
		ASSERT_FALSE(FloatOperator::ComplexIsApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsGreaterReal)
	{
		std::complex<double> first = { 5.0, 1.2 };
		std::complex<double> second = { 4.0, 1.2 };
		ASSERT_FALSE(FloatOperator::ComplexIsLessApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsGreaterNorm)
	{
		std::complex<double> first = { 4.0, -1.6 };
		std::complex<double> second = { 4.0, 1.2 };
		ASSERT_TRUE(!FloatOperator::ComplexIsLessApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsGreaterImag)
	{
		std::complex<double> first = { 4.0, 1.6 };
		std::complex<double> second = { 4.0, -1.6000001 };
		ASSERT_TRUE(!FloatOperator::ComplexIsLessApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsLessReal)
	{
		std::complex<double> first = { 4.0, 1.2 };
		std::complex<double> second = { 5.0, 1.2 };
		ASSERT_TRUE(!FloatOperator::ComplexIsGreaterApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsLessNorm)
	{
		std::complex<double> first = { 4.0, 1.2 };
		std::complex<double> second = { 4.0, -1.6 };
		ASSERT_TRUE(!FloatOperator::ComplexIsGreaterApprox(first, second, .0001));
	}
	
	TEST(Classifier, ComplexIsLessImag)
	{
		std::complex<double> first = { 4.0, -1.6000001 };
		std::complex<double> second = { 4.0, 1.6 };
		ASSERT_TRUE(!FloatOperator::ComplexIsGreaterApprox(first, second, .0001));
	}
}