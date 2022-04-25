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
private:

    void CheckValidTypes()
    {
        if(!(typeid(T) == typeid(float) || typeid(T) == typeid(double)))
            throw("The valid types are only float and double");
    }

    void CheckValidTFDimensions(size_t numeratorDegree, size_t denominatorDegree)
    {
        if(numeratorDegree > denominatorDegree)
            throw BadNumeratorException(numeratorDegree, denominatorDegree);
    }

    void CheckValidSSDimensions()
    {
        if(m_MatrixA.rows() != m_MatrixA.cols())
            throw BadStateMatrixException(m_MatrixA.rows(), m_MatrixA.cols());
        if(m_MatrixA.rows() != m_MatrixB.rows())
            throw BadInputMatrixException(m_MatrixA.rows(), m_MatrixB.rows());
        if(m_MatrixA.cols() != m_MatrixC.cols())
            throw BadOutputMatrixException(m_MatrixA.cols(), m_MatrixC.cols());
        if((m_MatrixB.cols()!= m_MatrixD.cols())||(m_MatrixC.rows() != m_MatrixD.rows()))
            throw BadDirectTransferMatrixException(m_MatrixC.rows(), m_MatrixB.cols(), m_MatrixD.rows(), m_MatrixD.cols());
    }

    void MonizeDenominator(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator);
    void DissociateDirectTransferTerm(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator, T& directTransferTerm);
    void BuildDMatrixFromTF(T directTransferTerm);
    void BuildAMatrixFromTF(const Eigen::Matrix<T, -1, 1>& denominator);
    void BuildBMatrixFromTF();
    void BuildCMatrixFromTF(const Eigen::Matrix<T, -1, 1>& numerator);

    void SetStatesMatricesFromTF(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator);
    void BuildControllabilityMatrix();
    void BuildObservabilityMatrix();

    Eigen::Matrix<T, -1, -1> m_MatrixA;
    Eigen::Matrix<T, -1, -1> m_MatrixB;
    Eigen::Matrix<T, -1, -1> m_MatrixC;
    Eigen::Matrix<T, -1, -1> m_MatrixD;

    Eigen::Matrix<T, -1, -1> m_ControllabilityMatrix;
    Eigen::Matrix<T, -1, -1> m_ObservabilityMatrix;
    Eigen::Matrix<std::complex<T>, -1, 1> m_Eigenvalues;
};

#include "DynamicSystem.inl"

#endif
