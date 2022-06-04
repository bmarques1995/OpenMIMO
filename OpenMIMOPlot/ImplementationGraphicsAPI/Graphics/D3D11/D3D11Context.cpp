#include "D3D11Context.hpp"

OpenMIMO::D3D11Context::D3D11Context(HWND window) :
    m_Window(window)
{
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
    sd.OutputWindow = m_Window;
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

OpenMIMO::D3D11Context::~D3D11Context()
{
    
}

void OpenMIMO::D3D11Context::CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    m_Device->CreateRenderTargetView(pBackBuffer, NULL, m_RenderTargetView.GetAddressOf());
    pBackBuffer->Release();
}

void OpenMIMO::D3D11Context::Update()
{
    m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), NULL);
    m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), m_ClearColor);
}

void OpenMIMO::D3D11Context::SetClearColor(float x, float y, float z, float w)
{
    m_ClearColor[0] = x;
    m_ClearColor[1] = y;
    m_ClearColor[2] = z;
    m_ClearColor[3] = w;
}

void OpenMIMO::D3D11Context::SetViewport(uint32_t width, uint32_t height)
{
    D3D11_VIEWPORT viewport;
    viewport.TopLeftX = .0f;
    viewport.Width = (float)width;
    viewport.TopLeftY = .0f;
    viewport.Height = (float)height;
    viewport.MinDepth = .0f;
    viewport.MaxDepth = 1.0f;

    m_DeviceContext->RSSetViewports(1,&viewport);

    m_RenderTargetView->Release();
    m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}

std::any OpenMIMO::D3D11Context::GetComponentConstructor() const
{
    GraphicsMinimal minimal;
    minimal.Device = m_Device.Get();
    minimal.DeviceContext = m_DeviceContext.Get();
    return minimal;
}

void OpenMIMO::D3D11Context::Present()
{
    m_SwapChain->Present(0, 0);
}
