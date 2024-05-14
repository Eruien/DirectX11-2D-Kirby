#include "LEndScene.h"
#include "LInput.h"

bool LEndScene::Init()
{
    g_fMapSizeX = m_MapSizeX;
    g_fMapSizeY = m_MapSizeY;

    m_pMainCamera->Create({ 0.0f, 0.0f, 1.0f }, { float(g_WindowWidth), float(g_WindowHeight) });
    m_pMainCamera->m_HalfMapX = m_MapSizeX;
    m_pMainCamera->m_HalfMapY = m_MapSizeY;

    m_pMapObj = new LPlaneObj;
    m_pMapObj->Set(m_pDevice, m_pImmediateContext);
    m_pMapObj->SetPos({ 0.0f, 0.0f, 1.0f });
    m_pMapObj->SetScale(LVector(g_fMapSizeX, g_fMapSizeY, 1.0f));
    m_pMapObj->Create(L"../../res/PVShader.hlsl", L"../../res/clear.png");

    return true;
}

void LEndScene::Process()
{
    if (m_pMapObj == nullptr)
    {
        Init();
    }

    m_pMapObj->Frame();
    m_pMapObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pMapObj->Render();

    if (LInput::GetInstance().m_dwKeyState[VK_ESCAPE] == DWORD(KeyState::KEY_PUSH))
    {
        Release();
        m_pOwner->SetTransition(Event::GOMAINSCENE);
        return;
    }
}

void LEndScene::Release()
{
    delete m_pMapObj;
    m_pMapObj = nullptr;
    delete m_pStartButton;
    m_pStartButton = nullptr;
}

LEndScene::LEndScene(LScene* parent) : SceneState(parent)
{
    m_pMainCamera = parent->m_pMainCamera;
    m_pDevice = parent->m_pDevice;
    m_pImmediateContext = parent->m_pImmediateContext;
}
LEndScene::~LEndScene() {}