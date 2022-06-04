#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"
#include "InterfaceGraphicsAPI/WindowController.hpp"

#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <WRL.h>

using Microsoft::WRL::ComPtr;

namespace OpenMIMO
{
    struct GraphicsMinimal
    {
        ID3D11Device* Device;
        ID3D11DeviceContext* DeviceContext;
    };

    class D3D11Context : public GraphicsContext
    {
    public:
        D3D11Context(HWND window);
        ~D3D11Context();

        virtual void Update() override;
        virtual void SetClearColor(float x, float y, float z, float w) override;
        virtual void SetViewport(uint32_t width, uint32_t height) override;
        virtual std::any GetComponentConstructor() const override;
        virtual void Present() override;

    private:
        float m_ClearColor[4] = { .0f,.0f,.0f,1.0f };
        HWND m_Window;

        ComPtr<ID3D11Device> m_Device;
        ComPtr<ID3D11DeviceContext> m_DeviceContext;
        ComPtr<IDXGISwapChain> m_SwapChain;
        ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
        void CreateRenderTarget();
    };
}

#endif
