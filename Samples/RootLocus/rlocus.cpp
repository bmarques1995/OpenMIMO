#include <OpenMIMO/RootLocusContainer.hpp>
#include <iostream>

int main()
{
	OpenMIMO::TransferFunction<double> system({ 1 }, { 1,6,5 });
	/*
		  1
	------------
	s^2 + 6s + 5
	*/
	OpenMIMO::RootLocusContainer<double> rLocus(system);

	std::cout << rLocus.GetRootLocus(1.5) << "\n";

	return 0;
}