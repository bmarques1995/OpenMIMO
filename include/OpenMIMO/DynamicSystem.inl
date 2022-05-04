template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator)
{
    CheckValidTypes();
    CheckValidTFDimensions(numerator.rows(), denominator.rows());
    SetStatesMatricesFromTF(numerator, denominator);
    m_Eigenvalues.resize(m_DynamicMatrix.rows(),1);
    m_Eigenvalues = m_DynamicMatrix.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, -1>& matrixA, const Eigen::Matrix<T, -1, -1>& matrixB, const Eigen::Matrix<T, -1, -1>& matrixC)
{
    CheckValidTypes();
    //construir exceções para tratativas
    m_DynamicMatrix = matrixA;
    m_InputMatrix = matrixB;
    m_OutputMatrix = matrixC;
    m_FeedForwardMatrix.resize(m_OutputMatrix.rows(), m_InputMatrix.cols());
    m_FeedForwardMatrix.setZero();
    CheckValidSSDimensions();
    m_Eigenvalues.resize(m_DynamicMatrix.rows(),1);
    m_Eigenvalues = m_DynamicMatrix.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline DynamicSystem<T>::DynamicSystem(const Eigen::Matrix<T, -1, -1>& dynamicMatrix, const Eigen::Matrix<T, -1, -1>& inputMatrix, const Eigen::Matrix<T, -1, -1>& outputMatrix, const Eigen::Matrix<T, -1, -1>& feedForwardMatrix)
{
    CheckValidTypes();
    //construir exceções para tratativas
    m_DynamicMatrix = dynamicMatrix;
    m_InputMatrix = inputMatrix;
    m_OutputMatrix = outputMatrix;
    m_FeedForwardMatrix = feedForwardMatrix;
    CheckValidSSDimensions();
    m_Eigenvalues.resize(m_DynamicMatrix.rows(),1);
    m_Eigenvalues = m_DynamicMatrix.eigenvalues();
    BuildControllabilityMatrix();
    BuildObservabilityMatrix();
}

template<typename T>
inline void DynamicSystem<T>::PrintMatrices()
{
    std::cout << "A: " << "\n";
    std::cout << m_DynamicMatrix << "\n";
    std::cout << "B: " << "\n";
    std::cout << m_InputMatrix << "\n";
    std::cout << "C: " << "\n";
    std::cout << m_OutputMatrix << "\n";
    std::cout << "D: " << "\n";
    std::cout << m_FeedForwardMatrix << "\n";
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
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetDynamicMatrix() const
{
    return m_DynamicMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetInputMatrix() const
{
    return m_InputMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetOutputMatrix() const
{
    return m_OutputMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetFeedForwardMatrix() const
{
    return m_FeedForwardMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetControllabilityMatrix() const
{
    return m_ControllabilityMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetObservabilityMatrix() const
{
    return m_ObservabilityMatrix;
}

template<typename T>
inline const Eigen::Matrix<T, -1, -1>& DynamicSystem<T>::GetEigenvalues() const
{
    return m_Eigenvalues;
}

//private members

template<typename T>
inline void DynamicSystem<T>::CheckValidTypes()
{
    if(!(typeid(T) == typeid(float) || typeid(T) == typeid(double)))
        throw BadTypeStartException();
}

template<typename T>
inline void DynamicSystem<T>::CheckValidTFDimensions(size_t numeratorDegree, size_t denominatorDegree)
{
    if(numeratorDegree > denominatorDegree)
            throw BadNumeratorException(numeratorDegree, denominatorDegree);
    
}

template<typename T>
inline void DynamicSystem<T>::CheckValidSSDimensions()
{
    if(m_DynamicMatrix.rows() != m_DynamicMatrix.cols())
        throw BadDynamicMatrixException(m_DynamicMatrix.rows(), m_DynamicMatrix.cols());
    if(m_DynamicMatrix.rows() != m_InputMatrix.rows())
        throw BadInputMatrixException(m_DynamicMatrix.rows(), m_InputMatrix.rows());
    if(m_DynamicMatrix.cols() != m_OutputMatrix.cols())
        throw BadOutputMatrixException(m_DynamicMatrix.cols(), m_OutputMatrix.cols());
    if((m_InputMatrix.cols()!= m_FeedForwardMatrix.cols())||(m_OutputMatrix.rows() != m_FeedForwardMatrix.rows()))
        throw BadFeedForwardMatrixException(m_OutputMatrix.rows(), m_InputMatrix.cols(), m_FeedForwardMatrix.rows(), m_FeedForwardMatrix.cols());
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
inline void DynamicSystem<T>::DissociateFeedForwardTerm(Eigen::Matrix<T, -1, 1>& numerator, Eigen::Matrix<T, -1, 1>& denominator, T& feedForwardTerm)
{
    if(numerator.rows() == denominator.rows())
    {
        feedForwardTerm = numerator(0) / denominator(0);
        auto numeratorCopy = numerator;
        numerator.resize((size_t)numerator.rows() - 1, 1);
        for(size_t i = 0; i < (size_t) denominator.rows() - 1; ++i)
            numerator(i) = numeratorCopy(i+1) - denominator(i+1) * feedForwardTerm;
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildFeedForwardMatrixFromTF(T directTransferTerm)
{
    m_FeedForwardMatrix.resize(1,1);
    m_FeedForwardMatrix(0,0) = directTransferTerm;
}

template<typename T>
inline void DynamicSystem<T>::BuildDynamicMatrixFromTF(const Eigen::Matrix<T, -1, 1>& denominator)
{
    m_DynamicMatrix.resize((size_t) denominator.rows() - 1, (size_t) denominator.rows() - 1);
    m_DynamicMatrix.setZero();

    for(size_t i = 0; i < (size_t)m_DynamicMatrix.rows() - 1; ++i)
    {
        m_DynamicMatrix(i, i +1) = (T)1.0;
    }

    for(size_t i = 0, rowsMatrixA = (size_t)(denominator.rows() - 1); i < rowsMatrixA; ++i)
    {
        m_DynamicMatrix(rowsMatrixA - 1, i) = (T)-1.0 * denominator(rowsMatrixA - i);
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildInputMatrixFromTF()
{
    m_InputMatrix.resize(m_DynamicMatrix.rows(),1);
    m_InputMatrix.setZero();

    m_InputMatrix(m_InputMatrix.rows() -1, 0) = 1.0f;
}

template<typename T>
inline void DynamicSystem<T>::BuildOutputMatrixFromTF(const Eigen::Matrix<T, -1, 1>& numerator)
{
    m_OutputMatrix.resize(1, m_DynamicMatrix.rows());
    m_OutputMatrix.setZero();

    for(size_t i = 0; i < (size_t)numerator.rows(); ++i)
    {
        m_OutputMatrix(0, i) = numerator(numerator.rows() - i - 1);
    }
}

template<typename T>
inline void DynamicSystem<T>::SetStatesMatricesFromTF(const Eigen::Matrix<T, -1, 1>& numerator, const Eigen::Matrix<T, -1, 1>& denominator)
{
    auto numeratorCopy = numerator;
    auto denominatorCopy = denominator;
    T directTransferTerm = (T)0.0;

    MonizeDenominator(numeratorCopy, denominatorCopy);
    DissociateFeedForwardTerm(numeratorCopy, denominatorCopy, directTransferTerm);

    BuildFeedForwardMatrixFromTF(directTransferTerm);
    BuildDynamicMatrixFromTF(denominatorCopy);
    BuildInputMatrixFromTF();
    BuildOutputMatrixFromTF(numeratorCopy);
}

template<typename T>
inline void DynamicSystem<T>::BuildControllabilityMatrix()
{
    m_ControllabilityMatrix.resize(m_DynamicMatrix.rows(), m_DynamicMatrix.cols() * m_InputMatrix.cols());
    auto controllabilityCol = m_InputMatrix;
    for(size_t i = 0; i < (size_t) m_DynamicMatrix.cols(); ++i)
    {
        if(i > 0)
            controllabilityCol = m_DynamicMatrix * controllabilityCol;

        for(size_t j = 0; j < (size_t) controllabilityCol.cols(); ++j)
            for(size_t k = 0; k < (size_t) controllabilityCol.rows(); ++k)
                m_ControllabilityMatrix(k,i*controllabilityCol.cols()+j) = controllabilityCol(k,j); 
    }
}

template<typename T>
inline void DynamicSystem<T>::BuildObservabilityMatrix()
{
    m_ObservabilityMatrix.resize(m_DynamicMatrix.rows() * m_OutputMatrix.rows(), m_DynamicMatrix.cols());
    auto observabilityRow = m_OutputMatrix;

    for(size_t i = 0; i < (size_t) m_DynamicMatrix.rows(); ++i)
    {
        if(i > 0)
            observabilityRow = observabilityRow * m_DynamicMatrix;
        for(size_t j = 0; j < (size_t) observabilityRow.rows(); ++j)
            for(size_t k = 0; k < (size_t) observabilityRow.cols(); ++k)
                m_ObservabilityMatrix(i*observabilityRow.rows() + j,k) = observabilityRow(j,k); 
    }
}
