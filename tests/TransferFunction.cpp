#include <gtest/gtest.h>
#include <iostream>
#include <OpenMIMO/TransferFunction.hpp>

namespace OpenMIMO
{
	TEST(TransferFunction, Multiply)
	{
		TransferFunction<double> output({ 1, 5 }, { 1, 5, 6 });
		TransferFunction<double> multiplier;
		multiplier = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 1, 3 }, { 1, 5 });
		output *= multiplier;
		TransferFunction<double> expectedOutput;
		expectedOutput = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 1 }, { 1, 2 });
		ASSERT_TRUE(expectedOutput.IsApproximated(output));
	}

	TEST(TransferFunction, Gain)
	{
		TransferFunction<double> output({ 1, 5 }, { 1, 5, 6 });
		double gain = 5.0;
		output *= gain;
		TransferFunction<double> expectedOutput;
		expectedOutput = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 5, 25 }, { 1, 5, 6 });
		ASSERT_TRUE(expectedOutput.IsApproximated(output));
	}

	TEST(TransferFunction, Add)
	{
		TransferFunction<double> output({ 1, 5 }, { 1, 14, 61, 104 });
		TransferFunction<double> adder;
		adder = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 1, 3 }, { 1, 6, 13 });
		output += adder;
		TransferFunction<double> expectedOutput;
		expectedOutput = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 1, 12, 29 }, { 1, 14, 61, 104 });
		ASSERT_TRUE(expectedOutput.IsApproximated(output));
	}

	TEST(TransferFunction, Subtract)
	{
		TransferFunction<double> output({ 1, 5 }, { 1, 14, 61, 104 });
		TransferFunction<double> adder;
		adder = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ 1, 3 }, { 1, 6, 13 });
		output -= adder;
		TransferFunction<double> expectedOutput;
		expectedOutput = std::make_pair<std::initializer_list<double>, std::initializer_list<double>>({ -1, -10, -19 }, { 1, 14, 61, 104 });
		ASSERT_TRUE(expectedOutput.IsApproximated(output));
	}

	TEST(TransferFunction, FinalValue)
	{
		TransferFunction<double> output({ 1, 5 }, { 1, 14, 61, 104 });
		ASSERT_TRUE(FloatOperator::IsApprox(5.0 / 104.0, output.GetFinalValue(), 1e-5));
	}
}