#include <gtest/gtest.h>
#include <OpenMIMO/DynamicSystem.hpp>
#include <OpenMIMO/utils/ComplexSortClassifier.hpp>
#include <iostream>

TEST(DynamicSystem, NumeratorDimensionError)
{
    Eigen::VectorXd tf_numerator(6);
    Eigen::VectorXd tf_denominator(5);
    ASSERT_THROW(new DynamicSystem<double>(tf_numerator, tf_denominator), BadNumeratorException);
}

/*
TEST(DynamicSystem, TypeInsertionError)
{   
    Eigen::MatrixXd dynamicMatrix(3,4);
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;
    ASSERT_THROW(new DynamicSystem<std::complex<float>>(dynamicMatrix, inputMatrix, outputMatrix), BadTypeStartException);
}
*/

TEST(DynamicSystem, DynamicMatrixDimensionError)
{   
    Eigen::MatrixXd dynamicMatrix(3,4);
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;
    
    ASSERT_THROW(new DynamicSystem<double>(dynamicMatrix, inputMatrix, outputMatrix), BadDynamicMatrixException);
}

TEST(DynamicSystem, InputMatrixDimensionError)
{   
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(1,4);
    Eigen::MatrixXd outputMatrix;

    ASSERT_THROW(new DynamicSystem<double>(dynamicMatrix, inputMatrix, outputMatrix), BadInputMatrixException);
}

TEST(DynamicSystem, OutputMatrixDimensionError)
{
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(4,1);
    Eigen::MatrixXd outputMatrix(4,1);

    ASSERT_THROW(new DynamicSystem<double>(dynamicMatrix, inputMatrix, outputMatrix), BadOutputMatrixException);
}

TEST(DynamicSystem, FeedForwardMatrixDimensionError)
{
    
    Eigen::MatrixXd dynamicMatrix(4,4);
    Eigen::MatrixXd inputMatrix(4,1);
    Eigen::MatrixXd outputMatrix(2,4);
    Eigen::MatrixXd feedForwardMatrix(1,2);

    ASSERT_THROW(new DynamicSystem<double>(dynamicMatrix, inputMatrix, outputMatrix, feedForwardMatrix), BadFeedForwardMatrixException);
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
        ASSERT_TRUE(dynamicMatrix.isApprox(dynamicSystem->GetDynamicMatrix(), .0001));
        ASSERT_TRUE(inputMatrix.isApprox(dynamicSystem->GetInputMatrix(), .0001));
        ASSERT_TRUE(outputMatrix.isApprox(dynamicSystem->GetOutputMatrix(), .0001));
        ASSERT_TRUE(feedForwardMatrix.isApprox(dynamicSystem->GetFeedForwardMatrix(),.0001));
        delete dynamicSystem;
    }
    catch(...)
    {
        ASSERT_TRUE(false);
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

    try
    {
        dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        ASSERT_TRUE(controllabilityMatrix.isApprox(dynamicSystem->GetControllabilityMatrix(), .0001));
        delete dynamicSystem;
    }

    catch(...)
    {
        ASSERT_TRUE(false);
    }
}

TEST(DynamicSystem, ExpectedObservabilityMatrix)
{
    DynamicSystem<double> *dynamicSystem;

    Eigen::MatrixXd dynamicMatrix;
    Eigen::MatrixXd inputMatrix;
    Eigen::MatrixXd outputMatrix;
    Eigen::MatrixXd feedforwardMatrix(2,1);

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

    try
    {
        dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix, feedforwardMatrix);
        ASSERT_TRUE(observabilityMatrix.isApprox(dynamicSystem->GetObservabilityMatrix(), .0001));
        delete dynamicSystem;
    }

    catch(...)
    {
        ASSERT_TRUE(false);
    } 
}

TEST(DynamicSystem, ExpectedEigenvalues)
{
    DynamicSystem<double> *dynamicSystem;
    Eigen::MatrixXd dynamicMatrix(3,3);
    Eigen::MatrixXd inputMatrix(3,1);
    Eigen::MatrixXd outputMatrix(1,3);

    dynamicMatrix << 0, 1, 0,
    0, 0, 1,
    -68, -49, -12;

    Eigen::VectorXcd expectedEigenvalues(3);

    expectedEigenvalues << std::complex<double>(-4.0,1.0),std::complex<double>(-4.0,0),std::complex<double>(-4.0,-1.0);

    try
    {
        dynamicSystem = new DynamicSystem(dynamicMatrix, inputMatrix, outputMatrix);
        std::sort(expectedEigenvalues.begin(), expectedEigenvalues.end(), ComplexGreater<double>);
        auto eigenvalues = dynamicSystem->GetEigenvalues();
        std::sort(eigenvalues.begin(), eigenvalues.end(), ComplexGreater<double>);
        ASSERT_TRUE(expectedEigenvalues.isApprox(eigenvalues,.0001));
        delete dynamicSystem;
    }

    catch(...)
    {
        ASSERT_TRUE(false);
    } 
}
