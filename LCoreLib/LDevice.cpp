#include "LDevice.h"

bool LDevice::SetDevice()
{
    UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    HRESULT hr = D3D11CreateDevice(
        NULL,
        m_DriverType,
        NULL,
        Flags,
        &m_FeatureLevels, 1,
        D3D11_SDK_VERSION,
        &m_pDevice,
        NULL,
        &m_pImmediateContext
    );

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "Create Device Error", "Error Box", MB_OK);
        return false;
    }

    return true;
}

bool LDevice::SetGIFactory()
{
    HRESULT hr = CreateDXGIFactory(
        __uuidof(IDXGIFactory), (LPVOID*)&m_pGIFactory
    );

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "Create DXGIFactory Error", "Error Box", MB_OK);
        return false;
    }

    return true;
}

bool LDevice::SetSwapChain()
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc = {0,};
    
    SwapChainDesc.BufferDesc.Width = 800;
    SwapChainDesc.BufferDesc.Height = 600;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 1;
    SwapChainDesc.OutputWindow = m_hWnd;
    SwapChainDesc.Windowed = true;

    HRESULT hr = m_pGIFactory->CreateSwapChain(m_pDevice, &SwapChainDesc, &m_pSwapChain);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "Create SwapChain Error", "Error Box", MB_OK);
        m_pGIFactory->Release();
        return false;
    }

    m_pGIFactory->Release();
    return true;
}

bool LDevice::SetRenderTargetView()
{
    HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pbackBuffer);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "SwapChain not get Buffer", "Error Box", MB_OK);
        return false;
    }

    hr = m_pDevice->CreateRenderTargetView(m_pbackBuffer, NULL, &m_pRenderTargetView);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "Create Render TargetView Error", "Error Box", MB_OK);
        m_pbackBuffer->Release();
        return false;
    }

    // 1 ¼³Á¤ÇÒ RenderTargetView°¹¼ö 2 RenderTargetView¹è¿­ 3 ½ºÅÄ½Çºä
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
    m_pbackBuffer->Release();

    return true;
}

bool LDevice::SetViewPort()
{
    // viewPort
    D3D11_VIEWPORT viewPort = {0,};
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.Width = 800.0f;
    viewPort.Height = 600.0f;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    // 1 ºäÆ÷Æ®ÀÇ °¹¼ö, 2ºäÆ÷Æ® ¹è¿­
    m_pImmediateContext->RSSetViewports(1, &viewPort);
    return true;
}

bool LDevice::DeviceInit()
{
    // »ç½Ç»ó create ÇÔ¼ö ÀÌ¸§ÀÌ °ãÃÄ¼­ SetÀ¸·Î ÁöÁ¤
    SetDevice();
    SetGIFactory();
    SetSwapChain();
    SetRenderTargetView();
    SetViewPort();
    return true;
}

bool LDevice::DeviceFrame()
{
    return true;
}

bool LDevice::DevicePreRender()
{
    float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
    
    return true;
}

bool LDevice::DevicePostRender()
{
    HRESULT hr = m_pSwapChain->Present(0, 0);
    if (FAILED(hr))
    {
        MessageBoxA(NULL, "buffer Present Error", "Error Box", MB_OK);
        return false;
    }

    return true;
}

bool LDevice::DeviceRelease()
{
    if (m_pSwapChain) m_pSwapChain->Release();
    if (m_pDevice) m_pDevice->Release();
    if (m_pImmediateContext) m_pImmediateContext->Release();
    if (m_pRenderTargetView) m_pRenderTargetView->Release();
    return true;
}

LDevice::~LDevice() {}
