#ifndef TEST_HPP
#define TEST_HPP

#include <Eigen/Eigen>
#include <iostream>

class Test
{
public:
    Test();
    static void Hello();
};

void Test::Hello()
{
    Eigen::Vector4f obj;
    obj = {.5f, 1.3f, .8f, .6f};
    std::cout << obj << std::endl;
}

#endif
