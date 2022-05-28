#include <gtest/gtest.h>
#include <OpenMIMO/DynamicSystemExceptions.hpp>
#include <iostream>

TEST(DynamicSystemExceptions, BadTypeStartExceptionMessage)
{
    OpenMIMO::BadTypeStartException e;
    ASSERT_STREQ(e.GetInfo(), "The only input types allowed are float and double, another will be denied");
}

TEST(DynamicSystemExceptions, BadNumeratorExceptionMessage)
{
    OpenMIMO::BadNumeratorException e(7,5);
    ASSERT_STREQ(e.GetInfo(), "was expected that the numerator degree was, at most 5, but its degree is 7.");
}

TEST(DynamicSystemExceptions, BadDynamicMatrixExceptionMessage)
{
    OpenMIMO::BadDynamicMatrixException e(7,5);
    ASSERT_STREQ(e.GetInfo(), "was expected that the dynamic matrix was square but its dimensions is 7x5.");
}

TEST(DynamicSystemExceptions, BadInputMatrixExceptionMessage)
{
    OpenMIMO::BadInputMatrixException e(7,5);
    ASSERT_STREQ(e.GetInfo(), "was expected that the input matrix had 7 rows, but it has 5.");
}

TEST(DynamicSystemExceptions, BadOutputMatrixExceptionMessage)
{
    OpenMIMO::BadOutputMatrixException e(7,5);
    ASSERT_STREQ(e.GetInfo(), "was expected that the output matrix had 7 columns, but it has 5.");
}

TEST(DynamicSystemExceptions, BadFeedForwardMatrixExceptionMessage)
{
    OpenMIMO::BadFeedForwardMatrixException e(7,5,4,3);
    ASSERT_STREQ(e.GetInfo(), "was expected that the direct transfer matrix had dimensions 7x5, but it has the following dimensions 4x3.");
}
