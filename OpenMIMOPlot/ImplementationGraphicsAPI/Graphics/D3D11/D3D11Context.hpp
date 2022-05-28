#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"
#include "InterfaceGraphicsAPI/WindowController.hpp"

#include <string>
#include <d3d11.h>
#include <WRL.h>

using Microsoft::WRL::ComPtr;

struct GraphicsMinimal
{
    ID3D11Device* Device;
    ID3D11DeviceContext* DeviceContext;
};

class D3D11Context : public GraphicsContext
{
    friend class WIN32Controller;
private:
    float m_ClearColor[4] = {.0f,.0f,.0f,1.0f};
    WindowController* m_WindowController;

    ComPtr<ID3D11Device> m_Device;
    ComPtr<ID3D11DeviceContext> m_DeviceContext;
    ComPtr<IDXGISwapChain> m_SwapChain;
    ComPtr<ID3D11RenderTargetView> m_MainRenderTargetView;
    void CreateRenderTarget();
public:
    D3D11Context(WindowController* controller);
    ~D3D11Context();

    virtual void Update() override;
    virtual void SetClearColor(float x, float y, float z, float w) override;
    virtual std::any GetComponentConstructor() const override;
    virtual void Present() override;
};

#endif
