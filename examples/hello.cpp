#include <OpenMIMO/DynamicSystem.hpp>

int main()
{
    Eigen::VectorXd tf_numerator(5); // = {2, 5, 7};
    Eigen::VectorXd tf_denominator(5);// = {1, 5, 6};
    tf_numerator(0) = 2.0f;
    tf_numerator(1) = 5.0f;
    tf_numerator(2) = 7.0f;
    tf_denominator(0) = 2.0f;
    tf_denominator(1) = 34.0f;
    tf_denominator(2) = 202.0f;
    tf_denominator(3) = 494.0f;
    tf_denominator(4) = 420.0f;
    tf_numerator.transpose();
    tf_denominator.transpose();
    DynamicSystem<double>* system;
    system = new DynamicSystem<double>(tf_numerator, tf_denominator);
    system->PrintMatrices();
    delete system;
    return 0;
}