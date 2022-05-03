#ifndef DYNAMIC_SYSTEM_HPP
#define DYNAMIC_SYSTEM_HPP

#include <Eigen/Dense>
#include <iostream>

#include "DynamicSystemExceptions.hpp"

template<class T>
class DynamicSystem
{
public:
    
    DynamicSystem(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator);
    DynamicSystem(const Eigen::Matrix<T, -1, -1>& matrixA, const Eigen::Matrix<T, -1, -1>& matrixB, const Eigen::Matrix<T, -1, -1>& matrixC);
    DynamicSystem(const Eigen::Matrix<T, -1, -1>& matrixA, const Eigen::Matrix<T, -1, -1>& matrixB, const Eigen::Matrix<T, -1, -1>& matrixC, const Eigen::Matrix<T, -1, -1>& matrixD);
    
    void PrintMatrices();

    const Eigen::Matrix<T, -1, -1>& GetDynamicMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetInputMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetOutputMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetFeedForwardMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetControllabilityMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetObservabilityMatrix() const;
    const Eigen::Matrix<T, -1, -1>& GetEigenvalues() const;
private:

    void CheckValidTypes();
    void CheckValidTFDimensions(size_t numeratorDegree, size_t denominatorDegree);
    void CheckValidSSDimensions();

    void MonizeDenominator(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator);
    void DissociateFeedForwardTerm(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator, T& directTransferTerm);
    void BuildFeedForwardMatrixFromTF(T directTransferTerm);
    void BuildDynamicMatrixFromTF(const Eigen::Matrix<T, -1, 1>& denominator);
    void BuildInputMatrixFromTF();
    void BuildOutputMatrixFromTF(const Eigen::Matrix<T, -1, 1>& numerator);

    void SetStatesMatricesFromTF(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator);
    void BuildControllabilityMatrix();
    void BuildObservabilityMatrix();

    Eigen::Matrix<T, -1, -1> m_DynamicMatrix;
    Eigen::Matrix<T, -1, -1> m_InputMatrix;
    Eigen::Matrix<T, -1, -1> m_OutputMatrix;
    Eigen::Matrix<T, -1, -1> m_FeedForwardMatrix;

    Eigen::Matrix<T, -1, -1> m_ControllabilityMatrix;
    Eigen::Matrix<T, -1, -1> m_ObservabilityMatrix;
    Eigen::Matrix<std::complex<T>, -1, 1> m_Eigenvalues;
};

#include "DynamicSystem.inl"

#endif
