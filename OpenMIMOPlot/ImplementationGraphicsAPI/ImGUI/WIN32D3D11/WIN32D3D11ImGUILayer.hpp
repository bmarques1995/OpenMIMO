#ifndef WIN32_D3D11_IMGUI_LAYER_HPP
#define WIN32_D3D11_IMGUI_LAYER_HPP

#include <GLFW/glfw3.h>
#include "Core/ImGUILayer.hpp"
#include <complex>

#include <windows.h>
#include <d3d11.h>

class WIN32D3D11ImGUILayer : public ImGUILayer
{
private:

    HWND m_Window;
    ID3D11Device* m_Device;
    ID3D11DeviceContext* m_DeviceContext;

    std::complex<double> poles[3];
    
    double real_poles[3];
    double imag_poles[3];
    int bar_data[11] = { 5,9,7,3,14,25,63,17,81,19,105 };
public:
    WIN32D3D11ImGUILayer(HWND window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
    ~WIN32D3D11ImGUILayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;

    virtual void BeginFrame() override;
    virtual void EndFrame() override;
};

#endif
