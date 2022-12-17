#include <OpenMIMO/BodeContainer.hpp>
#include <iostream>

int main()
{
	OpenMIMO::TransferFunction<double> system({ 1 }, { 1,6,5 });
	/*
	      1
	------------
	s^2 + 6s + 5
	*/
	OpenMIMO::BodeContainer<double> bode(system);

	std::cout << bode.GetBodeValues(1.5) << "\n";

	return 0;
}