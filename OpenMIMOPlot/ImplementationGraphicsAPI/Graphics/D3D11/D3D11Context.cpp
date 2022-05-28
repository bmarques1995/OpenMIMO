#include "D3D11Context.hpp"
#include <GLFW/glfw3.h>

D3D11Context::D3D11Context(WindowController* controller) :
    m_WindowController(controller)
{
    HWND window = std::any_cast<HWND>(m_WindowController->GetNativeWindow());
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = window;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    
    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        createDeviceFlags,
        featureLevelArray,
        2,
        D3D11_SDK_VERSION,
        &sd,
        m_SwapChain.GetAddressOf(),
        m_Device.GetAddressOf(),
        &featureLevel,
        m_DeviceContext.GetAddressOf()
    );
    if(hr != S_OK)
        exit(1);

    CreateRenderTarget();
}

D3D11Context::~D3D11Context()
{
    
}

void D3D11Context::CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_Device->CreateRenderTargetView(pBackBuffer, NULL, m_MainRenderTargetView.GetAddressOf());
    pBackBuffer->Release();
}

void D3D11Context::Update()
{
    m_DeviceContext->OMSetRenderTargets(1, m_MainRenderTargetView.GetAddressOf(), NULL);
    m_DeviceContext->ClearRenderTargetView(m_MainRenderTargetView.Get(), m_ClearColor);
}

void D3D11Context::SetClearColor(float x, float y, float z, float w)
{
    m_ClearColor[0] = x;
    m_ClearColor[1] = y;
    m_ClearColor[2] = z;
    m_ClearColor[3] = w;
}

std::any D3D11Context::GetComponentConstructor() const
{
    GraphicsMinimal minimal;
    minimal.Device = m_Device.Get();
    minimal.DeviceContext = m_DeviceContext.Get();
    return minimal;
}

void D3D11Context::Present()
{
    m_SwapChain->Present(0, 0);
}
