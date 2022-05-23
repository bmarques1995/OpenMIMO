#ifndef GLFW_GL4_IMGUI_LAYER_HPP
#define GLFW_GL4_IMGUI_LAYER_HPP

#include <GLFW/glfw3.h>
#include "Core/ImGUILayer.hpp"
#include <complex>

class GLFWGL4ImGUILayer : public ImGUILayer
{
private:
    GLFWwindow* m_WindowPtr;
    
    std::complex<double> poles[3];
    
    double real_poles[3];
    double imag_poles[3];
    int bar_data[11] = { 5,9,7,3,14,25,63,17,81,19,105 };
public:
    GLFWGL4ImGUILayer(GLFWwindow* windowPtr, std::string_view layerName = "ImGUIDebugLayer");
    ~GLFWGL4ImGUILayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

    virtual void BeginFrame() override;
    virtual void EndFrame() override;
};

#endif
