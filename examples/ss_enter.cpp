#include <OpenMIMO/DynamicSystem.hpp>

int main()
{
    Eigen::MatrixXd states(4,4);
    states << 0, 1, 0, 0, 
    0, 0, 1, 0,
    0, 0, 0, 1,
    -210, -247,-101, -17;

    Eigen::MatrixXd input(4,2);
    input << 0, 0,
    1, 0,
    0, 0,
    0, 1;

    Eigen::MatrixXd output(2,4);
    output << 1,0,0,0,
    0, 0, 1, 0;

    Eigen::MatrixXd directTransfer(2,3);
    directTransfer.setZero();

    DynamicSystem<double>* system;
    try
    {
        system = new DynamicSystem<double>(states, input, output);
    }
    catch(DynamicSystemException& e)
    {
        std::cout << e.GetInfo() << "\n";
    }
    if(system != nullptr)
        system->PrintMatrices();
    delete system;
    return 0;
}
