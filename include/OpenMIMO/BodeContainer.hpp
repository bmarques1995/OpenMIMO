#ifndef BODE_CONTAINER_HPP
#define BODE_CONTAINER_HPP

#include "TransferFunction.hpp"

namespace OpenMIMO
{
	template<typename T>
	class BodeContainer
	{
	public:
		BodeContainer();
		BodeContainer(const TransferFunction<T>& plant);

		void operator=(const TransferFunction<T>& plant);

		std::complex<T> GetBodeValues(T frequency);

		static std::complex<T> ToPolar(std::complex<T> rectangular);
	private:
		TransferFunction<T> m_System;
		Eigen::Matrix<std::complex<T>, -1, 1> m_Zeros;
		Eigen::Matrix<std::complex<T>, -1, 1> m_Poles;
	};
}
#include "BodeContainer.inl"

#endif