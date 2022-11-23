template<typename T>
inline OpenMIMO::Polynomial<T>::Polynomial(const std::initializer_list<T>& elements, T tolerance) :
    m_Tolerance(tolerance)
{
    InitializePolynomial(elements);
}

template<typename T>
inline OpenMIMO::Polynomial<T>::Polynomial()
{
    m_Polynomial.resize(1);
    m_Polynomial.setZero();
    m_PolynomialLinear = true;
    m_Tolerance = (T)1e-6;
}

template<typename T>
inline OpenMIMO::Polynomial<T> OpenMIMO::Polynomial<T>::operator+(Polynomial& p1)
{
    Polynomial result;

    if (p1.m_Polynomial.rows() > this->m_Polynomial.rows())
        result.m_Polynomial = p1.m_Polynomial;
    else
        result.m_Polynomial = this->m_Polynomial;

    for (size_t i = 0; (i < (size_t)p1.m_Polynomial.rows()) && (i < (size_t)this->m_Polynomial.rows()); ++i)
    {
        result.m_Polynomial(i) = p1.m_Polynomial(i) + this->m_Polynomial(i);
    }

    return result;
}

template<typename T>
inline OpenMIMO::Polynomial<T> OpenMIMO::Polynomial<T>::operator-(Polynomial& p1)
{
    auto subtractingCopy = (p1.m_Polynomial * -1.0);

    Polynomial result;
    if (p1.m_Polynomial.rows() > this->m_Polynomial.rows())
        result.m_Polynomial = subtractingCopy;
    else
        result.m_Polynomial = this->m_Polynomial;

    for (size_t i = 0; (i < (size_t)subtractingCopy.rows()) && (i < (size_t)this->m_Polynomial.rows()); ++i)
    {
        result.m_Polynomial(i) = subtractingCopy(i) + this->m_Polynomial(i);
    }

    return result;
}

template<typename T>
inline OpenMIMO::Polynomial<T> OpenMIMO::Polynomial<T>::operator*(Polynomial& p1)
{
    Polynomial result;
    if (((size_t)p1.m_Polynomial.rows() != 0) && ((size_t)this->m_Polynomial.rows() != 0)) {
        result.m_Polynomial.resize(this->m_Polynomial.rows() + p1.m_Polynomial.rows() - 1);
        result.m_Polynomial.setZero();
        for (size_t i = 0; i < (size_t)this->m_Polynomial.rows(); i++)
        {
            for (size_t j = 0; j < (size_t)p1.m_Polynomial.rows(); j++)
            {
                result.m_Polynomial(i + j) += this->m_Polynomial(i) * p1.m_Polynomial(j);
            }
        }
    }
    return result;
}

template<typename T>
inline OpenMIMO::Polynomial<T> OpenMIMO::Polynomial<T>::operator*(T gain)
{
    Polynomial result;
    if (((size_t)this->m_Polynomial.rows() != 0)) {
        result.m_Polynomial.resize(this->m_Polynomial.rows());
        result.m_Polynomial.setZero();
        for (size_t i = 0; i < (size_t)this->m_Polynomial.rows(); i++)
        {
            result.m_Polynomial(i) += this->m_Polynomial(i) * gain;
        }
    }
    return result;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::operator+=(Polynomial& p1)
{
    *this = *this + p1;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::operator-=(Polynomial& p1)
{
    *this = *this - p1;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::operator*=(Polynomial& p1)
{
    *this = (*this) * p1;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::operator*=(T gain)
{
    *this = (*this) * gain;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::operator=(const std::initializer_list<T>& elements)
{
    this->InitializePolynomial(elements);
}

template<typename T>
inline const Eigen::Matrix<T, -1, 1>& OpenMIMO::Polynomial<T>::GetPolynomial() const
{
	return m_Polynomial;
}

template<typename T>
inline const size_t OpenMIMO::Polynomial<T>::GetPolynomialSize() const
{
    return (size_t) m_Polynomial.rows();
}

template<typename T>
inline Eigen::Matrix<std::complex<T>, -1, 1> OpenMIMO::Polynomial<T>::GetRoots() const
{
    Eigen::Matrix<T, -1, -1> rootsMatrix;
    rootsMatrix.resize((size_t) m_Polynomial.rows() - 1, (size_t) m_Polynomial.rows() - 1);
    rootsMatrix.setZero();

    for(size_t i = 0; i < (size_t)(rootsMatrix.rows() - 1); ++i)
    {
        if (((size_t)rootsMatrix.rows() == 0) || ((size_t)rootsMatrix.cols() == 0))
            break;
        rootsMatrix(i, i +1) = (T)1.0;
    }

    for(size_t i = 0, rowsMatrixA = (size_t)(m_Polynomial.rows() - 1); i < rowsMatrixA; ++i)
    {
        if (((size_t)rootsMatrix.rows() > 0) && ((size_t)rootsMatrix.cols() > 0))
            rootsMatrix(rowsMatrixA - 1, i) = (T)-1.0 * m_Polynomial(i)/m_Polynomial(rowsMatrixA);
    }

    Eigen::Matrix<std::complex<T>, -1, 1> roots;
    if (((size_t)rootsMatrix.rows() > 0) && ((size_t)rootsMatrix.cols() > 0))
    {
        roots = rootsMatrix.eigenvalues();
        Sorter::Sort(roots.begin(), roots.end(), FloatOperator::ComplexIsLess<double>, (size_t)roots.size());
    }
    else
    {
        roots.resize(0);
    }
    return roots;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::InsertRoot(pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& root, const pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& end)
{
    if (FloatOperator::IsApprox<T>((*root).imag(), (T).0, m_Tolerance))
        InsertRealRoot(*root);
    else
        InsertComplexRoot(root,end);
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::InsertRealRoot(const std::complex<T>& root)
{
    Polynomial<T> temp;
    temp = { 1.0, root.real() * (-1.0) };
    *this *= temp;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::InsertComplexRoot(pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& root, const pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>, -1, 1>>& end)
{
    Polynomial<T> temp;
    std::complex<T> first = *root;
    temp = { 1.0, first.real() * (-2.0), first.real() * first.real() + first.imag()* first.imag()};
    *this *= temp;
}

template<typename T>
inline void OpenMIMO::Polynomial<T>::InitializePolynomial(const std::initializer_list<T>& elements)
{
    m_Polynomial.resize(elements.size());
    size_t it = 0;
    for (auto&& i : elements)
    {
        m_Polynomial(m_Polynomial.rows() - 1 - it) = i;
        it++;
    }
    m_PolynomialLinear = true;
}
