template<typename T>
inline OpenMIMO::TransferFunction<T>::TransferFunction(std::initializer_list<T> numerator, std::initializer_list<T> denominator) : 
	m_Numerator(numerator,1e-6), m_Denominator(denominator,1e-6)
{}

template<typename T>
inline OpenMIMO::TransferFunction<T>::TransferFunction() :
	m_Numerator({(T)0},1e-6), m_Denominator({(T)1},1e-6)
{}

template<typename T>
inline OpenMIMO::TransferFunction<T> OpenMIMO::TransferFunction<T>::operator+(TransferFunction& t1)
{
	TransferFunction result;
	result.m_Numerator = this->m_Numerator * t1.m_Denominator + t1.m_Numerator * this->m_Denominator;
	result.m_Denominator = this->m_Denominator * t1.m_Denominator;
	result.Simplify();
	return result;
}

template<typename T>
inline OpenMIMO::TransferFunction<T> OpenMIMO::TransferFunction<T>::operator-(TransferFunction& t1)
{
	TransferFunction result;
	result.m_Numerator = this->m_Numerator * t1.m_Denominator - t1.m_Numerator * this->m_Denominator;
	result.m_Denominator = this->m_Denominator * t1.m_Denominator;
	result.Simplify();
	return result;
}


template<typename T>
inline OpenMIMO::TransferFunction<T> OpenMIMO::TransferFunction<T>::operator*(TransferFunction& t1)
{
	TransferFunction result;
	result.m_Numerator = this->m_Numerator * t1.m_Numerator;
	result.m_Denominator = this->m_Denominator * t1.m_Denominator;
	result.Simplify();
	return result;
}

template<typename T>
inline OpenMIMO::TransferFunction<T> OpenMIMO::TransferFunction<T>::operator*(T gain)
{
	TransferFunction result;
	result.m_Numerator = this->m_Numerator * gain;
	result.m_Denominator = this->m_Denominator;
	return result;
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::operator+=(TransferFunction& t1)
{
	*this = *this + t1;
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::operator-=(TransferFunction& t1)
{
	*this = *this - t1;
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::operator*=(TransferFunction& t1)
{
	*this = *this * t1;
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::operator*=(T gain)
{
	*this = *this * gain;
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::operator=(const std::pair<std::initializer_list<T>, std::initializer_list<T>>& numeratorAndDenominator)
{
	this->m_Numerator = numeratorAndDenominator.first;
	this->m_Denominator = numeratorAndDenominator.second;
}

template<typename T>
inline bool OpenMIMO::TransferFunction<T>::IsApproximated(const TransferFunction& tf2)
{
	return (GetNumerator().GetPolynomial().isApprox(tf2.GetNumerator().GetPolynomial(), 1e-5) && GetDenominator().GetPolynomial().isApprox(tf2.GetDenominator().GetPolynomial(), 1e-5));
}

template<typename T>
inline const OpenMIMO::Polynomial<T>& OpenMIMO::TransferFunction<T>::GetNumerator() const
{
	return m_Numerator;
}

template<typename T>
inline const OpenMIMO::Polynomial<T>& OpenMIMO::TransferFunction<T>::GetDenominator() const
{
	return m_Denominator;
}

template<typename T>
inline T OpenMIMO::TransferFunction<T>::GetFinalValue() const
{
	return m_Numerator.GetPolynomial()(0) / m_Denominator.GetPolynomial()(0);
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::Reset()
{
	T numGain = (m_Numerator.GetPolynomial()((size_t)(m_Numerator.GetPolynomial().size() - 1)));
	T denGain = (m_Denominator.GetPolynomial()((size_t)(m_Denominator.GetPolynomial().size() - 1)));
	m_Numerator = { numGain / denGain };
	m_Denominator = { (T)1.0 };
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::ResetWithGain()
{
	T numGain = (m_Numerator.GetPolynomial()((size_t)(m_Numerator.GetPolynomial().size() - 1)));
	T denGain = (m_Denominator.GetPolynomial()((size_t)(m_Denominator.GetPolynomial().size() - 1)));
	m_Numerator = { numGain / denGain };
	m_Denominator = { (T)1.0 };
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::FilterRoots(Eigen::Matrix<std::complex<T>, -1, 1>& roots)
{
	size_t filteredRootsSize = (size_t)roots.rows();
	auto clone = roots;
	for (auto it = roots.begin(); it < roots.end(); it++)
	{
		if (FloatOperator::IsLess(it->imag(), (T)0.0, 1.0e-6))
			filteredRootsSize--;
	}
	roots.resize(filteredRootsSize);
	auto rootsIt = roots.begin();
	for (auto it = clone.begin(); it < clone.end(); it++)
	{
		if (FloatOperator::IsGreaterApprox(it->imag(), (T)0.0, 1.0e-6))
		{
			*rootsIt = *it;
			rootsIt++;
		}
			
	}
}

template<typename T>
inline void OpenMIMO::TransferFunction<T>::Simplify()
{
	//obter interse��o de conjuntos
	auto numeratorRoots = m_Numerator.GetRoots();
	auto denominatorRoots = m_Denominator.GetRoots();
	ResetWithGain();
	FilterRoots(numeratorRoots);
	FilterRoots(denominatorRoots);
	pointer_based_stl_iterator<Eigen::Matrix<std::complex<T>,-1,1>> numIt = numeratorRoots.begin();
	auto denIt = denominatorRoots.begin();
	for (; numIt != numeratorRoots.end() || denIt != denominatorRoots.end();)
	{
		Polynomial<T> temp;
		//n�o se comporta bem com uma toler�ncia 1e-6
		if(!FloatOperator::ComplexIsApprox(*numIt,*denIt,1.0E-5) && numIt != numeratorRoots.end() && denIt != denominatorRoots.end())
		{
			if(FloatOperator::ComplexIsGreater(*numIt, *denIt,1.0E-5))
			{
				m_Denominator.InsertRoot(denIt, denominatorRoots.end());
				denIt++;
			}
			else
			{
				m_Numerator.InsertRoot(numIt, numeratorRoots.end());
				numIt++;
			}
		}
		else
		{
			numIt++;
			denIt++;
		}
		if (numIt == numeratorRoots.end() && denIt != denominatorRoots.end())
		{
			m_Denominator.InsertRoot(denIt, denominatorRoots.end());
			denIt++;
		}
		if (denIt == denominatorRoots.end() && numIt != numeratorRoots.end())
		{
			m_Numerator.InsertRoot(numIt, numeratorRoots.end());
			numIt++;
		}
	}
	
}