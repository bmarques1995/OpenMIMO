#ifndef ROOT_LOCUS_CONTAINER_HPP
#define ROOT_LOCUS_CONTAINER_HPP

#include "TransferFunction.hpp"

namespace OpenMIMO
{
	template<typename T>
	class RootLocusContainer
	{
	public:
		RootLocusContainer();
		RootLocusContainer(const TransferFunction<T>& plant);
		RootLocusContainer(const TransferFunction<T>& plant, const TransferFunction<T>& controller);
		RootLocusContainer(const TransferFunction<T>& plant, const TransferFunction<T>& controller, const TransferFunction<T>& sensor);

		void operator=(const TransferFunction<T>& plant);

		Eigen::Matrix<std::complex<T>, -1, 1> GetRootLocus(T gain);
	private:
		TransferFunction<T> m_System;
	};
}
#include "RootLocusContainer.inl"

#endif