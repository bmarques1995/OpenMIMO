template<typename T>
inline OpenMIMO::BodeContainer<T>::BodeContainer() {}

template<typename T>
inline OpenMIMO::BodeContainer<T>::BodeContainer(const TransferFunction<T>& plant) :
	m_System(plant)
{
	m_Zeros = m_System.GetNumerator().GetRoots();
	TransferFunction<T>::FilterRoots(m_Zeros);
	m_Poles = m_System.GetDenominator().GetRoots();
	TransferFunction<T>::FilterRoots(m_Poles);
}

template<typename T>
inline void OpenMIMO::BodeContainer<T>::operator=(const TransferFunction<T>& plant)
{
	this->m_System = plant;
	m_Zeros = m_System.GetNumerator().GetRoots();
	TransferFunction<T>::FilterRoots(m_Zeros);
	m_Poles = m_System.GetDenominator().GetRoots();
	TransferFunction<T>::FilterRoots(m_Poles);
}

template<typename T>
inline std::complex<T> OpenMIMO::BodeContainer<T>::GetBodeValues(T frequency)
{
	std::complex<T> bode((T)0.0, (T)0.0);
	
	bode = std::complex<T>(20 * log10(m_System.GetFinalValue()), 0.0);

	for (size_t i = 0; i < (size_t)m_Zeros.rows(); i++)
	{
		std::complex<T> currentBode;
		if ((size_t)m_Zeros.rows() > 0)
		{
			if (FloatOperator::IsApprox(m_Zeros(i).imag(), 0.0, 1e-5))
			{
				currentBode = std::complex<T>((T)1.0, (T)((-1.0) * frequency) / m_Poles(i).real());
				currentBode = ToPolar(currentBode);
				bode = std::complex<T>(bode.real() + 20 * log10(currentBode.real()), bode.imag() + currentBode.imag());
			}
			else
			{
				T lastTerm = m_Zeros(i).real() * m_Zeros(i).real() + m_Zeros(i).imag() * m_Zeros(i).imag();
				currentBode = std::complex<T>(lastTerm - (frequency * frequency), (T)2.0 * frequency * m_Zeros(i).real());
				currentBode = ToPolar(currentBode);
				bode = std::complex<T>(bode.real() + 20 * log10(currentBode.real()) - 20 * log10(lastTerm), bode.imag() + currentBode.imag());
			}
		}
	}

	for (size_t i = 0; i < (size_t)m_Poles.rows(); i++)
	{
		std::complex<T> currentBode;
		if ((size_t)m_Poles.rows() > 0)
		{
			if (FloatOperator::IsApprox(m_Poles(i).imag(), 0.0, 1e-5))
			{
				//TODO rec to pol
				currentBode = std::complex<T>((T)1.0, (T)((-1.0)*frequency) / m_Poles(i).real());
				currentBode = ToPolar(currentBode);
				bode = std::complex<T>(bode.real() - 20 * log10(currentBode.real()), bode.imag() - currentBode.imag());
			}
			else
			{
				T lastTerm = m_Poles(i).real() * m_Poles(i).real() + m_Poles(i).imag() * m_Poles(i).imag();
				currentBode = std::complex<T>(lastTerm - (frequency * frequency), (T)2.0 * frequency * m_Zeros(i).real());
				currentBode = ToPolar(currentBode);
				bode = std::complex<T>(bode.real() - 20 * log10(currentBode.real()) + 20 * log10(lastTerm), bode.imag() - currentBode.imag());
			}
		}
	}

	return bode;
}

template <typename T>
inline std::complex<T> OpenMIMO::BodeContainer<T>::ToPolar(std::complex<T> rectangular)
{
	std::complex<T> polar(sqrt(rectangular.real()*rectangular.real() + rectangular.imag()*rectangular.imag()), atan2(rectangular.imag(), rectangular.real()));
	return polar;
}
