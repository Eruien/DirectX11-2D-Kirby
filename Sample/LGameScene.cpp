#include "LGameScene.h"
#include "LInput.h"
#include "LGlobal.h"
#include "LWrite.h"

void LGameScene::ReleaseText()
{
    LWrite::GetInstance().m_TextList.clear();
}

bool LGameScene::PlayerInit()
{
    m_pOwner->Init();
    return true;
}

bool LGameScene::Init()
{
    g_fMapSizeX = m_MapSizeX;
    g_fMapSizeY = m_MapSizeY;

    // 카메라 범위 제한용
    m_pMainCamera->m_HalfMapX = m_MapSizeX;
    m_pMainCamera->m_HalfMapY = m_MapSizeY;

    m_pMapObj = new LPlaneObj;
    m_pMapObj->Set(m_pDevice, m_pImmediateContext);
    m_pMapObj->SetScale(LVector(g_fMapSizeX, g_fMapSizeY, 1.0f));
    m_pMapObj->Create(L"../../res/PVShader.hlsl", L"../../res/background.png");

    m_pFloor = new LPlaneObj;
    m_pFloor->Set(m_pDevice, m_pImmediateContext);
    m_pFloor->SetPos(LVector(0.0f, -g_fMapSizeY + 30, 1.0f));
    m_pFloor->SetScale(LVector(1500.0f, 30.0f, 1.0f));
    m_pFloor->SetBox(m_pFloor->m_vPosition, m_pFloor->m_vScale.x * 2, m_pFloor->m_vScale.y * 2, 1.0f);
    m_pFloor->Create(L"../../res/PVShader.hlsl", L"../../res/kirbyblock1.png");

    m_pDoor = new LPlaneObj;
    m_pDoor->Set(m_pDevice, m_pImmediateContext);
    m_pDoor->SetPos(LVector(+g_fMapSizeX - 100.0f, -g_fMapSizeY + 60.0f + 42.0f, 1.0f));
    m_pDoor->SetScale(LVector(30.0f, 42.0f, 1.0f));
    m_pDoor->SetBox(m_pDoor->m_vPosition, m_pDoor->m_vScale.x * 2, m_pDoor->m_vScale.y * 2, 1.0f);
    m_pDoor->Create(L"../../res/PVShader.hlsl", L"../../res/kirbydoor.png");

    m_pPlayer = m_pOwner->m_pPlayer;
   
    // 플레이어 범위 제한용
    m_pPlayer->m_HalfMapX = m_MapSizeX;
    m_pPlayer->m_HalfMapY = m_MapSizeY;
    m_pPlayer->m_vPosition.x = -1500.0f + 48.0f;
    m_pPlayer->m_vPosition.y = -300.0f + 24.0f + 64.0f;

    m_pMonster = new LMonster;
    m_pMonster->Init();
    m_pMonster->FSM(FSMType::Monster);
    m_pMonster->Set(m_pDevice, m_pImmediateContext);
    m_pMonster->SetPos({ 0.0f, -200.0f, 1.0f });
    m_pMonster->SetScale(LVector(24.0f, 24.0f, 1.0f));
    m_pMonster->SetBox(m_pMonster->m_vPosition, m_pMonster->m_vScale.x * 2, m_pMonster->m_vScale.y * 2, 1.0f);
    m_pMonster->Create(L"../../res/PVShader.hlsl", L"../../res/monster/beam.png");
    
    m_MonsterList.push_back(m_pMonster);

    m_pMonster = new LMonster;
    m_pMonster->Init();
    m_pMonster->FSM(FSMType::Monster);
    m_pMonster->Set(m_pDevice, m_pImmediateContext);
    m_pMonster->SetPos({ 400.0f, -200.0f, 1.0f });
    m_pMonster->SetScale(LVector(24.0f, 24.0f, 1.0f));
    m_pMonster->SetBox(m_pMonster->m_vPosition, m_pMonster->m_vScale.x * 2, m_pMonster->m_vScale.y * 2, 1.0f);
    m_pMonster->Create(L"../../res/PVShader.hlsl", L"../../res/monster/beam.png");
  
    m_MonsterList.push_back(m_pMonster);

    ReleaseText();

    m_GameSound = LSoundMgr::GetInstance().Load(L"../../res/sound/greengreens.mp3");
    m_GameSound->Play();
    return true;
}

void LGameScene::Process()
{
    // scene전환할때 임시 화면
    /*m_SceneDelaysStart += g_fSPF;

    if (m_SceneDelaysStart <= m_SceneDelaysEnd)
    {
        return;
    }*/

    if (m_pMapObj == nullptr)
    {
        PlayerInit();
        Init();
    }

    m_pMapObj->Frame();
    m_pFloor->Frame();
    m_pDoor->Frame();
    for (auto monster : m_MonsterList)
    {
        monster->Frame();
        monster->Process(m_pPlayer);
    }
    m_pPlayer->Frame();
    m_pPlayer->Process();
    m_pPlayer->m_LifeCounter->Frame();
     
    // 어떤 몬스터가 충돌했는지 알려주기
    for (auto monster : m_MonsterList)
    {
        if (m_pPlayer->m_pEffect->m_Box.CollisionRect(monster->m_Box))
        {
            m_pPlayer->SetCollisionMonster(monster);
        }
    }
    
    // 바닥이랑 충돌했는지 표시
    if (m_pPlayer->m_Box.CollisionRect(m_pFloor->m_Box))
    {
        m_pPlayer->m_isFloor = true;
        m_pPlayer->m_FloorBox = m_pFloor->m_Box;
    }
    else
    {
        m_pPlayer->m_isFloor = false;
    }
    
    // 몬스터 바닥이랑 충돌표시
    for (auto monster : m_MonsterList)
    {
        if (monster->m_Box.CollisionRect(m_pFloor->m_Box))
        {
            monster->m_isFloor = true;
            monster->m_FloorBox = m_pFloor->m_Box;
        }
        else
        {
            monster->m_isFloor = false;
        }
    }
    
    // 카메라 위치랑 플레이어 위치 동기화
    m_pMainCamera->m_vCameraPos = m_pPlayer->m_vPosition;

    // Render

    m_pMapObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pMapObj->Render();
    m_pFloor->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pFloor->Render();
    m_pDoor->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pDoor->Render();
    for (auto monster : m_MonsterList)
    {
        monster->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
        monster->Render();
    }
    m_pPlayer->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->Render();
    m_pPlayer->m_pEffect->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->m_LifeCounter->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->m_LifeCounter->Render();

    for (auto iter = m_MonsterList.begin(); iter != m_MonsterList.end();)
    {
        if ((*iter)->m_DeleteFlag)
        {
            delete *iter;
            iter = m_MonsterList.erase(iter);
        }
        else
        {
            iter++;
        }
    }
 
    if (m_pPlayer->m_Box.CollisionRect(m_pDoor->m_Box))
    {
        if (LInput::GetInstance().m_dwKeyState[VK_UP] == DWORD(KeyState::KEY_PUSH))
        {
            LSoundMgr::GetInstance().GetPtr(L"door.wav")->Play(false);
            Release();
            m_SceneDelaysStart = 0.0f;
            m_pOwner->SetTransition(Event::GONEXTSCENE);
            return;
        }
    }

    if (LInput::GetInstance().m_dwKeyState['P'] == DWORD(KeyState::KEY_PUSH))
    {
        Release();
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GONEXTSCENE);
        return;
    }
    
    if (LInput::GetInstance().m_dwKeyState[VK_ESCAPE] == DWORD(KeyState::KEY_PUSH))
    {
        Release();
        delete m_pPlayer;
        m_pPlayer = nullptr;
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GOMAINSCENE);
        return;
    }
}

void LGameScene::Release()
{
    delete m_pMapObj;
    m_pMapObj = nullptr;
    delete m_pFloor;
    m_pFloor = nullptr;
    delete m_pDoor;
    m_pDoor = nullptr;
    
    for (auto monster : m_MonsterList)
    {
        delete monster;
    }
    m_MonsterList.clear();
    m_GameSound->Stop();
}

LGameScene::LGameScene(LScene* parent) : SceneState(parent)
{
    m_pMainCamera = parent->m_pMainCamera;
    m_pDevice = parent->m_pDevice;
    m_pImmediateContext = parent->m_pImmediateContext;
}
LGameScene::~LGameScene() {}