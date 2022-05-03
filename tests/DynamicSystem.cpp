#include <gtest/gtest.h>
#include <OpenMIMO/DynamicSystem.hpp>
#include <iostream>

TEST(DynamicSystem, NumeratorDimensionError)
{
    DynamicSystem<double> *dynamicSystem;
    Eigen::VectorXd tf_numerator(6);
    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW({
        try
        {
            dynamicSystem = new DynamicSystem(tf_numerator, tf_denominator);
        }
        catch( const BadNumeratorException& e )
        {
            throw;
        }
    }, BadNumeratorException);
}

TEST(DynamicSystem, DynamicMatrixDimensionError)
{
    DynamicSystem<double> *dynamicSystem;
    
    Eigen::MatrixXd dynamicMatrix(3,4);
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;
    Eigen::MatrixXd feedForwardMatrix;

    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW({
        try
        {
            dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        }
        catch( const BadDynamicMatrixException& e )
        {
            throw;
        }
    }, BadDynamicMatrixException);
}

TEST(DynamicSystem, InputMatrixDimensionError)
{
    DynamicSystem<double> *dynamicSystem;
    
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(1,4);
    Eigen::MatrixXd outputMatrix;
    Eigen::MatrixXd feedForwardMatrix;

    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW({
        try
        {
            dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        }
        catch( const BadInputMatrixException& e )
        {
            throw;
        }
    }, BadInputMatrixException);
}

TEST(DynamicSystem, OutputMatrixDimensionError)
{
    DynamicSystem<double> *dynamicSystem;
    
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(4,1);
    Eigen::MatrixXd outputMatrix(4,1);
    Eigen::MatrixXd feedForwardMatrix;

    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW({
        try
        {
            dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        }
        catch( const BadOutputMatrixException& e )
        {
            throw;
        }
    }, BadOutputMatrixException);
}

TEST(DynamicSystem, FeedForwardMatrixDimensionError)
{
    DynamicSystem<double> *dynamicSystem;
    
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(4,1);
    Eigen::MatrixXd outputMatrix(2,4);
    Eigen::MatrixXd feedForwardMatrix(1,2);

    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW({
        try
        {
            dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix, feedForwardMatrix);
        }
        catch( const BadFeedForwardMatrixException& e)
        {
            throw;
        }
    }, BadFeedForwardMatrixException);
}

//Melhorar, adicionar numerador de ordem 5
TEST(DynamicSystem, TransferFunctionToSpaceOfStates)
{
    DynamicSystem<double> *dynamicSystem;
    Eigen::VectorXd tf_numerator(5);
    Eigen::VectorXd tf_denominator(5);
    tf_numerator << 2, 34, 204, 542, 706;
    tf_denominator << 2, 34, 202, 494, 420;
    
    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;
    Eigen::MatrixXd feedForwardMatrix;

    std::array<bool, 4> passed = {false, false, false, false};

    dynamicMatrix.resize(4,4);
    dynamicMatrix << 0, 1, 0, 0,
    0,0,1,0,
    0,0,0,1,
    -210, -247, -101, -17;

    inputMatrix.resize(4,1);
    inputMatrix << 0,0,0,1;

    outputMatrix.resize(1,4);
    outputMatrix << 143, 24, 1, 0;

    feedForwardMatrix.resize(1,1);
    feedForwardMatrix << 1;
    
    try
    {
        dynamicSystem = new DynamicSystem(tf_numerator, tf_denominator);
        passed[0] = dynamicMatrix.isApprox(dynamicSystem->GetDynamicMatrix(), .0001);
        passed[1] = inputMatrix.isApprox(dynamicSystem->GetInputMatrix(), .0001);
        passed[2] = outputMatrix.isApprox(dynamicSystem->GetOutputMatrix(), .0001);
        passed[3] = feedForwardMatrix.isApprox(dynamicSystem->GetFeedForwardMatrix(),.0001);
    }
    catch(...)
    {
    }

    for (size_t i = 0; i < passed.size(); i++)
    {
        ASSERT_TRUE(passed[i]);
    }

}

TEST(DynamicSystem, ExpectedControllabilityMatrix)
{
    DynamicSystem<double> *dynamicSystem;

    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;

    Eigen::MatrixXd controllabilityMatrix(3,6);

    dynamicMatrix.resize(3,3);
    inputMatrix.resize(3,2);
    outputMatrix.resize(1,3);

    dynamicMatrix << 2, 5, 7,
    9, 8, 3,
    6, 5, 8;

    inputMatrix << 2, 5,
    4, 7,
    6, 5;

    controllabilityMatrix << 2, 5, 66, 80, 1032, 1475,
    4, 7, 68, 116, 1378, 1963,
    6, 5, 80, 105, 1376, 1900;
    
    bool passed = false;

    try
    {
        dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        passed = controllabilityMatrix.isApprox(dynamicSystem->GetControllabilityMatrix(), .0001);
    }

    catch(...)
    {
    }

    ASSERT_TRUE(passed);
}

TEST(DynamicSystem, ExpectedObservabilityMatrix)
{
    DynamicSystem<double> *dynamicSystem;

    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;

    Eigen::MatrixXd observabilityMatrix(6, 3);

    dynamicMatrix.resize(3,3);
    inputMatrix.resize(3,1);
    outputMatrix.resize(2,3);

    dynamicMatrix << 1, 5, 3,
    7, 5, 4,
    4, 6, 8;

    outputMatrix << 1, 7, 4,
    5, 6, 12;

    observabilityMatrix << 1, 7, 4,
    5, 6, 12,
    66, 64, 63,
    95, 127, 135,
    766, 1028, 958,
    1524, 1920, 1873;
    
    bool passed = false;

    try
    {
        dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        passed = observabilityMatrix.isApprox(dynamicSystem->GetObservabilityMatrix(), .0001);
    }

    catch(...)
    {
    }

    ASSERT_TRUE(passed);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}