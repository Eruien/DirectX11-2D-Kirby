#include "LBossScene.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBossScene::Init()
{
    // 전체 맵사이즈 변경
    g_fMapSizeX = m_MapSizeX;
    g_fMapSizeY = m_MapSizeY;

    // 카메라 밖을 벗어나지 않게
    m_pMainCamera->m_HalfMapX = m_MapSizeX;
    m_pMainCamera->m_HalfMapY = m_MapSizeY;

    m_pMapObj = new LPlaneObj;
    m_pMapObj->Set(m_pDevice, m_pImmediateContext);
    m_pMapObj->SetScale(LVector(g_fMapSizeX, g_fMapSizeY, 1.0f));
    m_pMapObj->Create(L"../../res/PVShader.hlsl", L"../../res/bossmap.png");

    // 256 x 64
    m_pFloor = new LPlaneObj;
    m_pFloor->Set(m_pDevice, m_pImmediateContext);
    m_pFloor->SetScale(LVector(400.0f, 32.0f, 1.0f));
    m_pFloor->SetPos(LVector(0.0f, -g_fMapSizeY + 32, 1.0f));
    m_pFloor->SetBox(m_pFloor->m_vPosition, m_pFloor->m_vScale.x * 2, m_pFloor->m_vScale.y * 2, 1.0f);
    m_pFloor->Create(L"../../res/PVShader.hlsl", L"../../res/bosstile.png");

    // 플레이어가 맵밖을 벗어나지 
    m_pPlayer = m_pOwner->m_pPlayer;
    m_pPlayer->m_HalfMapX = m_MapSizeX;
    m_pPlayer->m_HalfMapY = m_MapSizeY;
    m_pPlayer->m_vPosition.x = -400.0f + 48.0f;
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

    // boss rect 54x54
    m_pBoss = new LBoss;
    m_pBoss->m_StartPos = { 0.0f, 0.0f, 1.0f };
    m_pBoss->m_HalfMapsizeX = m_MapSizeX;
    m_pBoss->m_HalfMapsizeY = m_MapSizeY;
    m_pBoss->FSM(FSMType::BOSS);
    m_pBoss->Set(m_pDevice, m_pImmediateContext);
    m_pBoss->SetScale(LVector(72.0f, 72.0f, 1.0f));
    m_pBoss->SetBox(m_pBoss->m_vPosition, 108.0f, 108.0f, 1.0f);
    m_pBoss->Create(L"../../res/PVShader.hlsl", L"../../res/boss/bossnormal1.png");
    m_pBoss->Init();

    m_GameSound = LSoundMgr::GetInstance().Load(L"../../res/sound/moonlight.mp3");
    m_GameSound->Play();

    return true;
}

void LBossScene::CreateTwoMonster()
{
    m_pMonster = new LMonster;
    m_pMonster->Init();
    m_pMonster->FSM(FSMType::Monster);
    m_pMonster->Set(m_pDevice, m_pImmediateContext);
    m_pMonster->SetPos({ 400.0f, -200.0f, 1.0f });
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
}

void LBossScene::Process()
{
    // 맵바뀔때 임시 화면 
   /* m_SceneDelaysStart += g_fSPF;

    if (m_SceneDelaysStart <= m_SceneDelaysEnd)
    {
        return;
    }*/

    if (m_pMapObj == nullptr)
    {
        Init();
        if (m_pPlayer->m_CurrentState == State::FLY)
        {
            m_pPlayer->SetTransition(Event::INPUTATTACK);
        }
    }

    m_MonsterSpawnTimeStart += g_fSPF;

    if (m_MonsterSpawnTimeStart > m_MonsterSpawnTime)
    {
        CreateTwoMonster();
        m_MonsterSpawnTimeStart = 0.0f;
    }

    m_pMapObj->Frame();
    m_pFloor->Frame();
    for (auto monster : m_MonsterList)
    {
        monster->Frame();
        monster->Process(m_pPlayer);
    }
    m_pBoss->Frame();
    m_pBoss->Process(m_pPlayer);
    m_pBoss->m_LifeCounter->Frame();
    m_pPlayer->Frame();
    m_pPlayer->Process();
    m_pPlayer->m_LifeCounter->Frame();

    for (auto razer : m_pBoss->m_RazerList)
    {
        razer->Frame();
    }

    for (auto star : m_pBoss->m_StarList)
    {
        if (!star->m_IsDirectionCal)
        {
            star->SetTarget(m_pPlayer->m_Box.m_Center);
            star->m_IsDirectionCal = true;
        }
    }
   
    for (auto star : m_pBoss->m_StarList)
    {
        if (star->m_vPosition.x < -m_MapSizeX + star->m_vScale.x)
        {
            star->m_fDirection.x *= -1.0f;
            star->m_vPosition.x = -m_MapSizeX + star->m_vScale.x;
        }

        if (star->m_vPosition.y < -m_MapSizeY + star->m_vScale.y)
        {
            star->m_fDirection.y *= -1.0f;
            star->m_vPosition.y = -m_MapSizeY + star->m_vScale.y;
        }

        if (star->m_vPosition.x > m_MapSizeX - star->m_vScale.x)
        {
            star->m_fDirection.x *= -1.0f;
            star->m_vPosition.x = m_MapSizeX - star->m_vScale.x;
        }

        if (star->m_vPosition.y > m_MapSizeY - star->m_vScale.y)
        {
            star->m_fDirection.y *= -1.0f;
            star->m_vPosition.y = m_MapSizeY - star->m_vScale.y;
        }

        LVector vVelocity = star->m_fDirection * 400 * g_fSPF;

        star->m_vPosition = star->m_vPosition + vVelocity;
        star->m_vPosition.z = 0.0f;
        star->Frame();
    }

    m_pBoss->m_DamagedEffect->Frame();
         
    for (auto star : m_pBoss->m_StarList)
    {
        if (!m_pPlayer->isInvincibility)
        {
            if (m_pPlayer->m_Box.CollisionRect(star->m_Box))
            {
                m_pPlayer->isDamaged = true;
            }
        }
    }

    for (auto razer : m_pBoss->m_RazerList)
    {
        if (!m_pPlayer->isInvincibility)
        {
            if (m_pPlayer->m_Box.CollisionRect(razer->m_Box))
            {
                m_pPlayer->isDamaged = true;
            }
        }
    }

    if (m_pPlayer->m_InvincibilityTime)
    {
        m_pPlayer->m_InvincibilityStart += g_fSPF;
    }

    if (m_pPlayer->m_InvincibilityStart >= m_pPlayer->m_InvincibilityEnd)
    {
        m_pPlayer->isInvincibility = false;
        m_pPlayer->m_InvincibilityTime = false;
        m_pPlayer->isDamaged = false;
        m_pPlayer->m_InvincibilityStart = 0.0f;
    }

    // 보스랑 충돌했을때 알려주기
    if (m_pPlayer->m_pEffect->m_Box.CollisionRect(m_pBoss->m_Box))
    {
        m_pPlayer->SetCollisionBoss(m_pBoss);
    }

    if (m_pBoss->m_IsDamaged)
    {
        LSoundMgr::GetInstance().GetPtr(L"bosstakedamage.wav")->Play(false);
        m_pBoss->m_Life -= 1;
        m_pBoss->m_LifeCounter->m_AnimationIndex += 1;
        m_pBoss->m_InvincibilityTime = true;
        m_pBoss->isInvincibility = true;
        m_pBoss->m_IsDamaged = false;
    }

    if (m_pBoss->isInvincibility)
    {
        m_pBoss->m_DamagedEffect->m_Tex = LManager<LTexture>::GetInstance().Load(L"../../res/effect/damaged1.png");
    }
    else
    {
        m_pBoss->m_DamagedEffect->m_Tex = LManager<LTexture>::GetInstance().Load(L"../../res/none1.png");
    }

    if (m_pBoss->m_InvincibilityTime)
    {
        m_pBoss->m_InvincibilityStart += g_fSPF;
    }

    if (m_pBoss->m_InvincibilityStart >= m_pBoss->m_InvincibilityEnd)
    {
        m_pBoss->isInvincibility = false;
        m_pBoss->m_InvincibilityTime = false;
        m_pBoss->m_IsDamaged = false;
        m_pBoss->m_InvincibilityStart = 0.0f;
    }
   
    int shortDistance = 0;
    LMonster* pickMonster = nullptr;
    // 어떤 몬스터가 충돌했는지 알려주기
    for (auto& monster : m_MonsterList)
    {
        int dis = monster->m_Box.m_Center.x - m_pPlayer->m_Box.m_Center.x;
        
        if (shortDistance < dis)
        {
            shortDistance = dis;
            pickMonster = monster;
        }
    }

    if (pickMonster)
    {
        if (m_pPlayer->m_pEffect->m_Box.CollisionRect(pickMonster->m_Box))
        {
            m_pPlayer->SetCollisionMonster(pickMonster);
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

    // 카메라의 포지션을 플레이어의 포지션이랑 동기화함
    m_pMainCamera->m_vCameraPos = m_pPlayer->m_vPosition;

    // Render
    m_pMapObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pMapObj->Render();
    m_pFloor->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pFloor->Render();
    for (auto monster : m_MonsterList)
    {
        monster->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
        monster->Render();
    }
    m_pBoss->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pBoss->Render();
    m_pBoss->m_LifeCounter->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pBoss->m_LifeCounter->Render();
    m_pBoss->m_DamagedEffect->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pBoss->m_DamagedEffect->Render();
    m_pPlayer->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->Render();
    m_pPlayer->m_pEffect->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->m_LifeCounter->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
    m_pPlayer->m_LifeCounter->Render();

    for (auto razer : m_pBoss->m_RazerList)
    {
        razer->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
        razer->Render();
    }

    for (auto star : m_pBoss->m_StarList)
    {
        star->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matOrthoProjection);
        star->Render();
    }

    // delete flag가 달리면 몬스터를 삭제
    for (auto iter = m_MonsterList.begin(); iter != m_MonsterList.end();)
    {
        if ((*iter)->m_DeleteFlag)
        {
            delete* iter;
            iter = m_MonsterList.erase(iter);
        }
        else
        {
            iter++;
        }
    }

    // 적의 라이프가 없을 경우 클리어 화면
    if (m_pBoss->m_Life == 0)
    {
        Release();
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GONEXTSCENE);
        return;
    }

    // 플레이어의 라이프가 없을 경우 메인화면
    if (m_pPlayer->m_Life == 0)
    {
        Release();
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GOMAINSCENE);
        return;
    }

    // 문을 통과하면 맵을 넘어감
    if (LInput::GetInstance().m_dwKeyState['P'] == DWORD(KeyState::KEY_PUSH))
    {
        Release();
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GONEXTSCENE);
        return;
    }

    //esc를 누르면 메인화면으로 돌아감
    if (LInput::GetInstance().m_dwKeyState[VK_ESCAPE] == DWORD(KeyState::KEY_PUSH))
    {
        Release();
        m_SceneDelaysStart = 0.0f;
        m_pOwner->SetTransition(Event::GOMAINSCENE);
        return;
    }
}

void LBossScene::Release()
{
    delete m_pMapObj;
    m_pMapObj = nullptr;

    delete m_pFloor;
    m_pFloor = nullptr;

    delete m_pPlayer;
    m_pPlayer = nullptr;
    
    for (auto monster : m_MonsterList)
    {
        delete monster;
    }
    m_MonsterList.clear();

    delete m_pBoss;
    m_pBoss = nullptr;
    m_GameSound->Stop();
}

LBossScene::LBossScene(LScene* parent) : SceneState(parent)
{
    g_fMapSizeX = 800.0f;
    g_fMapSizeY = 600.0f;
    m_pMainCamera = parent->m_pMainCamera;
    m_pDevice = parent->m_pDevice;
    m_pImmediateContext = parent->m_pImmediateContext;
}
LBossScene::~LBossScene() {}