#include <gtest/gtest.h>

TEST(TestSuiteFail, TestFail)
{
    ASSERT_EQ(true, false);
}

TEST(TestSuitePass, TestPass)
{
    ASSERT_EQ(true, true);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}