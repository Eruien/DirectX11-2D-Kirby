#include "LCore.h"
#include "LGlobal.h"

bool LCore::Init() { return true; }
bool LCore::Frame() { return true; }
bool LCore::Render() { return true; }
bool LCore::Release() { return true; }

bool LCore::EngineInit()
{
    DeviceInit();
    LGlobal::g_pDevice = m_pDevice;
    LGlobal::g_pImmediateContext = m_pImmediateContext;
    LManager<LTexture>::GetInstance().Set(m_pDevice, m_pImmediateContext);
    LManager<LShader>::GetInstance().Set(m_pDevice, m_pImmediateContext);
    m_Gametimer.Init();
    m_pMainCamera = std::make_shared<LCamera>();
    m_pMainCamera->Init();
    LGlobal::g_pMainCamera = m_pMainCamera.get();
    LInput::GetInstance().Init();
    LWrite::GetInstance().Init();
    LWrite::GetInstance().Create(m_pSwapChain, m_hWnd);
	Init();
	return true;
}

bool LCore::EngineFrame()
{
    DeviceFrame();
    m_Gametimer.Frame();
    LInput::GetInstance().Frame();
    LWrite::GetInstance().Frame();
    m_pMainCamera->Frame();
	Frame();
	return true;
}

bool LCore::EngineRender()
{
    DevicePreRender();
    LWrite::GetInstance().PreRender();
	Render();
    m_pMainCamera->Render();
    m_Gametimer.Render();
    LWrite::GetInstance().Render();
    LInput::GetInstance().Render();
    LWrite::GetInstance().PostRender();
    DevicePostRender();
	return true;
}

bool LCore::EngineRelease()
{
    DeviceRelease();
    Release();
    m_Gametimer.Release();
    LWrite::GetInstance().Release();
    m_pMainCamera->Release();
    LInput::GetInstance().Release();
    LManager<LTexture>::GetInstance().Release();
    LManager<LShader>::GetInstance().Release();
    
	return true;
}

bool LCore::Run()
{
    EngineInit();

    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            EngineFrame();
            EngineRender();
        }
    }

    EngineRelease();

    return true;
}

LCore::~LCore() {}