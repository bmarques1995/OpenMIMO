template<typename T>
inline OpenMIMO::RootLocusContainer<T>::RootLocusContainer()
{
	TransferFunction<T>& plant({ 1 }, {1});
	m_System = plant;
}

template<typename T>
inline OpenMIMO::RootLocusContainer<T>::RootLocusContainer(const TransferFunction<T>& plant)
{
	m_System = plant;
}

template<typename T>
inline OpenMIMO::RootLocusContainer<T>::RootLocusContainer(const TransferFunction<T>& plant, const TransferFunction<T>& controller)
{
	m_System = plant * controller;
}

template<typename T>
inline OpenMIMO::RootLocusContainer<T>::RootLocusContainer(const TransferFunction<T>& plant, const TransferFunction<T>& controller, const TransferFunction<T>& sensor)
{
	m_System = plant * controller * sensor;
}

template<typename T>
inline void OpenMIMO::RootLocusContainer<T>::operator=(const TransferFunction<T>& plant)
{
	m_System = plant;
}

template<typename T>
inline Eigen::Matrix<std::complex<T>, -1, 1> OpenMIMO::RootLocusContainer<T>::GetRootLocus(T gain)
{
	Polynomial<T> numerator = m_System.GetNumerator();
	Polynomial<T> denominator = m_System.GetDenominator();
	Polynomial<T> rootLocus = denominator + (numerator * gain);
	Eigen::Matrix<std::complex<T>, -1, 1> roots = rootLocus.GetRoots();
	Sorter::Sort(roots.begin(), roots.end(), FloatOperator::ComplexIsGreater<T>, (size_t)roots.size());
	return roots;
}