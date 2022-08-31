template<typename T>
inline OpenMIMO::Polynomial<T>::Polynomial(std::list<T> elements)
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

template<typename T>
inline OpenMIMO::Polynomial<T>::Polynomial()
{
    m_PolynomialLinear = true;
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
inline const Eigen::Matrix<T, -1, 1>& OpenMIMO::Polynomial<T>::GetPolynomial() const
{
	return m_Polynomial;
}

