#include "Sample.h"
#include "LGlobal.h"
#include "LSoundMgr.h"

void Sample::CreateBlendState()
{
    D3D11_BLEND_DESC bsd = { 0, };
    bsd.RenderTarget[0].BlendEnable = true;
    bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

    bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    m_pDevice->CreateBlendState(&bsd, &m_AlphaBlend);
}

bool Sample::Init()
{
    LSoundMgr::GetInstance().Load(L"../../res/sound/abilityGet.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/door.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/kirbyinhale.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/runStart.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/slide.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/kirbyairattack.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/cancleability.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/flyup.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/jump.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/bosstakedamage.wav");
    LSoundMgr::GetInstance().Load(L"../../res/sound/kirbytakedamage.wav");
    CreateBlendState();

    m_pMainCamera->Create({0.0f, 0.0f, 0.0f}, LVector2(m_WindowWidth, m_WindowHeight));

    m_Scene = new LScene;
    m_Scene->SceneSet(m_pMainCamera, m_pDevice, m_pImmediateContext);
    m_Scene->FSM(FSMType::SCENE);

    return true;
}

bool Sample::Frame()
{
    return true;
}

bool Sample::Render()
{
    m_pImmediateContext->OMSetBlendState(m_AlphaBlend, 0, -1);
    m_Scene->Process();
 
    return true;
}

bool Sample::Release()
{
    return true;
}

Sample::~Sample() {}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR IpCmdLine, int nCmdShow)
{
    Sample win;
    win.SetRegisterWindowClass(hInstance);
    win.SetCreateWindow(L"DirectX11 2D Kirby", 800, 600);
    win.Run();
}


