#ifndef TEST_LAYER_HPP
#define TEST_LAYER_HPP

#include "Core/Layer.hpp"
#include <complex>

class TestLayer : public Layer
{
private:
    std::complex<double> poles[3];
    
    double real_poles[3];
    double imag_poles[3];
    int bar_data[11] = { 5,9,7,3,14,25,63,17,81,19,105 };
    
    void ImGUIRender();
public:
    TestLayer();
    ~TestLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
};

#endif
