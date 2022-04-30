template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator)
{
    CheckValidTypes();
    CheckValidTFDimensions(numerator.rows(), denominator.rows());
    SetStatesMatricesFromTF(numerator, denominator);
    m_Eigenvalues.resize(m_MatrixA.rows(),1);
    m_Eigenvalues = m_MatrixA.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, -1>& matrixA, const Eigen::Matrix<T, -1, -1>& matrixB, const Eigen::Matrix<T, -1, -1>& matrixC)
{
    CheckValidTypes();
    //construir exceções para tratativas
    m_MatrixA = matrixA;
    m_MatrixB = matrixB;
    m_MatrixC = matrixC;
    m_MatrixD.resize(m_MatrixC.rows(), m_MatrixB.cols());
    m_MatrixD.setZero();
    CheckValidSSDimensions();
    m_Eigenvalues.resize(m_MatrixA.rows(),1);
    m_Eigenvalues = m_MatrixA.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, -1>& matrixA, const Eigen::Matrix<T, -1, -1>& matrixB, const Eigen::Matrix<T, -1, -1>& matrixC, const Eigen::Matrix<T, -1, -1>& matrixD)
{
    CheckValidTypes();
    //construir exceções para tratativas
    m_MatrixA = matrixA;
    m_MatrixB = matrixB;
    m_MatrixC = matrixC;
    m_MatrixD = matrixD;
    CheckValidSSDimensions();
    m_Eigenvalues.resize(m_MatrixA.rows(),1);
    m_Eigenvalues = m_MatrixA.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline void DynamicSystem<T>::PrintMatrices()
{
    std::cout << "A: " << "\n";
    std::cout << m_MatrixA << "\n";
    std::cout << "B: " << "\n";
    std::cout << m_MatrixB << "\n";
    std::cout << "C: " << "\n";
    std::cout << m_MatrixC << "\n";
    std::cout << "D: " << "\n";
    std::cout << m_MatrixD << "\n";
    std::cout << "Eigenvalues: " << "\n";
    std::cout << m_Eigenvalues << "\n";
    std::cout << "Controllability: " << "\n";
    std::cout << m_ControllabilityMatrix << "\n";
    std::cout << "Controllability Rank: " << "\n";
    std::cout << m_ControllabilityMatrix.fullPivLu().rank() << "\n";
    std::cout << "Observability: " << "\n";
    std::cout << m_ObservabilityMatrix << "\n";
    std::cout << "Observability Rank: " << "\n";
    std::cout << m_ObservabilityMatrix.fullPivLu().rank() << "\n";
}

template<typename T>
inline void DynamicSystem<T>::MonizeDenominator(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator)
{
    if(denominator(0) != (T)1.0)
    {
        T correction = 1.0/denominator(0);
        for(size_t i=0, rowsNumerator = (size_t) numerator.rows(); i < rowsNumerator; ++i)
        {
            numerator(i,0) *= correction;
        }

        for(size_t i=0, rowsDenominator = (size_t) denominator.rows(); i < rowsDenominator; ++i)
        {
            denominator(i,0) *= correction;
        }
    }
}

template<typename T>
inline void DynamicSystem<T>::DissociateDirectTransferTerm(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator, T& directTransferTerm)
{
    if(numerator.rows() == denominator.rows())
    {
        directTransferTerm = numerator(0) / denominator(0);
        auto numeratorCopy = numerator;
        numerator.resize((size_t)numerator.rows() - 1, 1);
        for(size_t i = 0; i < (size_t) denominator.rows() - 1; ++i)
            numerator(i) = numeratorCopy(i+1) - denominator(i+1) * directTransferTerm;
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildDMatrixFromTF(T directTransferTerm)
{
    m_MatrixD.resize(1,1);
    m_MatrixD(0,0) = directTransferTerm;
}

template<typename T>
inline void DynamicSystem<T>::BuildAMatrixFromTF(const Eigen::Matrix<T, -1, 1>& denominator)
{
    m_MatrixA.resize((size_t) denominator.rows() - 1, (size_t) denominator.rows() - 1);
    m_MatrixA.setZero();

    for(size_t i = 0; i < m_MatrixA.rows() - 1; ++i)
    {
        m_MatrixA(i, i +1) = (T)1.0;
    }

    for(size_t i = 0, rowsMatrixA = (size_t)(denominator.rows() - 1); i < rowsMatrixA; ++i)
    {
        m_MatrixA(rowsMatrixA - 1, i) = (T)-1.0 * denominator(rowsMatrixA - i);
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildBMatrixFromTF()
{
    m_MatrixB.resize(m_MatrixA.rows(),1);
    m_MatrixB.setZero();

    m_MatrixB(m_MatrixB.rows() -1, 0) = 1.0f;
}

template<typename T>
inline void DynamicSystem<T>::BuildCMatrixFromTF(const Eigen::Matrix<T, -1, 1>& numerator)
{
    m_MatrixC.resize(1, m_MatrixA.rows());
    m_MatrixC.setZero();

    for(size_t i = 0; i < numerator.rows(); ++i)
    {
        m_MatrixC(0, i) = numerator(numerator.rows() - i - 1);
    }
}

template<typename T>
inline void DynamicSystem<T>::SetStatesMatricesFromTF(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator)
{
    auto numeratorCopy = numerator;
    auto denominatorCopy = denominator;
    T directTransferTerm = (T)0.0;

    MonizeDenominator(numeratorCopy, denominatorCopy);
    DissociateDirectTransferTerm(numeratorCopy, denominatorCopy, directTransferTerm);

    BuildDMatrixFromTF(directTransferTerm);
    BuildAMatrixFromTF(denominatorCopy);
    BuildBMatrixFromTF();
    BuildCMatrixFromTF(numeratorCopy);
}

template<typename T>
inline void DynamicSystem<T>::BuildControllabilityMatrix()
{
    m_ControllabilityMatrix.resize(m_MatrixA.rows(), m_MatrixA.cols() * m_MatrixB.cols());
    auto controllabilityCol = m_MatrixB;
    for(size_t i = 0; i < (size_t) m_MatrixA.cols(); ++i)
    {
        if(i > 0)
            controllabilityCol = m_MatrixA * controllabilityCol;

        for(size_t j = 0; j < (size_t) controllabilityCol.cols(); ++j)
            for(size_t k = 0; k < (size_t) controllabilityCol.rows(); ++k)
                m_ControllabilityMatrix(k,i*controllabilityCol.cols()+j) = controllabilityCol(k,j); 
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildObservabilityMatrix()
{
    m_ObservabilityMatrix.resize(m_MatrixA.rows() * m_MatrixC.rows(), m_MatrixA.cols());
    auto observabilityRow = m_MatrixC;

    for(size_t i = 0; i < (size_t) m_MatrixA.rows(); ++i)
    {
        if(i > 0)
            observabilityRow = observabilityRow * m_MatrixA;
        for(size_t j = 0; j < (size_t) observabilityRow.rows(); ++j)
            for(size_t k = 0; k < (size_t) observabilityRow.cols(); ++k)
                m_ObservabilityMatrix(i*observabilityRow.rows() + j,k) = observabilityRow(j,k); 
    }
}
