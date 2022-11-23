template<>
inline bool OpenMIMO::FloatOperator::IsApprox<double>(double first, double second, double variation)
{
	return ((second - variation) <= first) && ((second + variation) >= first);
}

template<>
inline bool OpenMIMO::FloatOperator::IsApprox<float>(float first, float second, float variation)
{
	return ((second - variation) <= first) && ((second + variation) >= first);
}

template<>
inline bool OpenMIMO::FloatOperator::IsGreater<double>(double first, double second, double variation)
{
	return first > (second + variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsGreater<float>(float first, float second, float variation)
{
	return first > (second + variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsLess<double>(double first, double second, double variation)
{
	return first < (second - variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsLess<float>(float first, float second, float variation)
{
	return first < (second - variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsGreaterApprox<double>(double first, double second, double variation)
{
	return !IsLess(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsGreaterApprox<float>(float first, float second, float variation)
{
	return !IsLess(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsLessApprox<double>(double first, double second, double variation)
{
	return !IsGreater(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::IsLessApprox<float>(float first, float second, float variation)
{
	return !IsGreater(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsApprox<double>(std::complex<double> first, std::complex<double> second, double variation)
{
	return (IsApprox(first.real(), second.real(), variation) && IsApprox(first.imag(), second.imag(), variation));
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsApprox<float>(std::complex<float> first, std::complex<float> second, float variation)
{
	return (IsApprox(first.real(), second.real(), variation) && IsApprox(first.imag(), second.imag(), variation));
}
template<>
inline bool OpenMIMO::FloatOperator::ComplexIsGreater<double>(std::complex<double> first, std::complex<double> second, double variation)
{
	return ((IsGreater(first.real(), second.real(), variation)) || 
		(IsApprox(first.real(), second.real(), variation) && IsGreater(std::norm(first), std::norm(second), variation) ||
		(IsApprox(std::norm(first), std::norm(second), variation)) && IsGreater(first.imag(), second.imag(), variation) ));
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsGreater<float>(std::complex<float> first, std::complex<float> second, float variation)
{
	return ((IsGreater(first.real(), second.real(), variation)) ||
		(IsApprox(first.real(), second.real(), variation) && IsGreater(std::norm(first), std::norm(second), variation) ||
			(IsApprox(std::norm(first), std::norm(second), variation)) && IsGreater(first.imag(), second.imag(), variation)));
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsLess<double>(std::complex<double> first, std::complex<double> second, double variation)
{
	return ((IsLess(first.real(), second.real(), variation)) ||
		(IsApprox(first.real(), second.real(), variation) && IsLess(std::norm(first), std::norm(second), variation) ||
			(IsApprox(std::norm(first), std::norm(second), variation)) && IsLess(first.imag(), second.imag(), variation)));
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsLess<float>(std::complex<float> first, std::complex<float> second, float variation)
{
	return ((IsLess(first.real(), second.real(), variation)) ||
		(IsApprox(first.real(), second.real(), variation) && IsLess(std::norm(first), std::norm(second), variation) ||
			(IsApprox(std::norm(first), std::norm(second), variation)) && IsLess(first.imag(), second.imag(), variation)));
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsGreaterApprox<double>(std::complex<double> first, std::complex<double> second, double variation)
{
	return !ComplexIsLess(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsGreaterApprox<float>(std::complex<float> first, std::complex<float> second, float variation)
{
	return !ComplexIsLess(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsLessApprox<double>(std::complex<double> first, std::complex<double> second, double variation)
{
	return !ComplexIsGreater(first, second, variation);
}

template<>
inline bool OpenMIMO::FloatOperator::ComplexIsLessApprox<float>(std::complex<float> first, std::complex<float> second, float variation)
{
	return !ComplexIsGreater(first, second, variation);
}
