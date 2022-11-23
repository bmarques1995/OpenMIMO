#include <OpenMIMO/DynamicSystem.hpp>

int main()
{
    Eigen::VectorXd tf_numerator(6); // = {2, 5, 7};
    Eigen::VectorXd tf_denominator(5);// = {1, 5, 6};
    tf_numerator(0) = 2.0;
    tf_numerator(1) = 5.0;
    tf_numerator(2) = 7.0;
    tf_denominator(0) = 2.0;
    tf_denominator(1) = 34.0;
    tf_denominator(2) = 202.0;
    tf_denominator(3) = 494.0;
    tf_denominator(4) = 420.0;
    tf_numerator.transpose();
    tf_denominator.transpose();
    DynamicSystem<double>* system;
    try
    {
        system = new DynamicSystem<double>(tf_numerator, tf_denominator);
    }
    catch(DynamicSystemException& e)
    {
        std::cout << e.GetInfo() << "\n";
    }
    if(system != nullptr)
        system->PrintMatrices();
    else
    std::cout << "null segment" << "\n";
    delete system;
    return 0;
}