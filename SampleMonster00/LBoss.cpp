#include "LBoss.h"
#include "LGlobal.h"
#include "LBossIdle.h"
#include "LBossStar.h"
#include "LBossRazerReady.h"
#include "LBossRazer.h"
#include "LBossThickRazer.h"
#include "LBossMove.h"

void LBoss::CreateRazer()
{
    LSpriteUVObj* razer = new LSpriteUVObj;
    razer->Set(m_pDevice, m_pImmediateContext);
    razer->SetScale(LVector(400.0f, 16.0f, 1.0f));
    razer->SetPos({ m_vPosition.x + razer->m_vScale.x + (m_Box.m_fWidth * 0.5f), m_vPosition.y - razer->m_vScale.y, 1.0f });
    razer->SetBox(razer->m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);
    razer->Create(L"../../res/PVShader.hlsl", L"../../res/effect/razer20.png");
    razer->SetUVAnimation(20, 2.0f);

    m_RazerList.push_back(razer);
}

void LBoss::CreateThickRazer()
{
    LSpriteUVObj* thickRazer = new LSpriteUVObj;
    thickRazer->Set(m_pDevice, m_pImmediateContext);
    thickRazer->SetScale(LVector(400.0f, 46.0f, 1.0f));
    thickRazer->SetPos({ m_vPosition.x + thickRazer->m_vScale.x + 54.0f, m_vPosition.y - 16.0f, 1.0f });
    thickRazer->SetBox(thickRazer->m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);
    thickRazer->Create(L"../../res/PVShader.hlsl", L"../../res/effect/thickrazer20.png");
    thickRazer->SetUVAnimation(20, 2.0f);

    m_RazerList.push_back(thickRazer);
}

void LBoss::ClearRazer()
{
    for (auto razer : m_RazerList)
    {
        delete razer;
    }

    m_RazerList.clear();
}

void LBoss::CreateThreeStar()
{
    LSpriteUVObj* threeStar = new LSpriteUVObj;
    threeStar->Set(m_pDevice, m_pImmediateContext);
    threeStar->SetPos({ m_vPosition.x - m_vScale.x , m_vPosition.y, 1.0f });
    threeStar->SetScale(LVector(24.0f, 24.0f, 1.0f));
    threeStar->SetBox(threeStar->m_vPosition, 48.0f, 48.0f, 1.0f);
    threeStar->Create(L"../../res/PVShader.hlsl", L"../../res/effect/star3.png");
    threeStar->SetUVAnimation(3, 1.0f);

    m_StarList.push_back(threeStar);

    threeStar = new LSpriteUVObj;
    threeStar->Set(m_pDevice, m_pImmediateContext);
    threeStar->SetPos({ m_vPosition.x - (m_vScale.x * 0.5f) , m_vPosition.y - (m_vScale.y * 0.5f), 1.0f });
    threeStar->SetScale(LVector(24.0f, 24.0f, 1.0f));
    threeStar->SetBox(threeStar->m_vPosition, 48.0f, 48.0f, 1.0f);
    threeStar->Create(L"../../res/PVShader.hlsl", L"../../res/effect/star3.png");
    threeStar->SetUVAnimation(3, 1.0f);

    m_StarList.push_back(threeStar);

    threeStar = new LSpriteUVObj;
    threeStar->Set(m_pDevice, m_pImmediateContext);
    threeStar->SetPos({ m_vPosition.x, m_vPosition.y - m_vScale.y, 1.0f });
    threeStar->SetScale(LVector(24.0f, 24.0f, 1.0f));
    threeStar->SetBox(threeStar->m_vPosition, 48.0f, 48.0f, 1.0f);
    threeStar->Create(L"../../res/PVShader.hlsl", L"../../res/effect/star3.png");
    threeStar->SetUVAnimation(3, 1.0f);

    m_StarList.push_back(threeStar);
}

void LBoss::ClearThreeStar()
{
    for (auto star : m_StarList)
    {
        delete star;
    }

    m_StarList.clear();
}

void LBoss::FSM(FSMType fsmType)
{
    auto iter = LFSMMgr::GetInstance().m_map.find(fsmType);

    if (LFSMMgr::GetInstance().m_map.end() == iter)
    {
        MessageBoxA(NULL, "FSMType Error", "Error Box", MB_OK);
        return;
    }

    m_pFsm = iter->second.get();

    m_pActionList.insert(std::make_pair(State::BOSSIDLE, std::make_unique<LBossIdle>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSSTAR, std::make_unique<LBossStar>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSRAZERREADY, std::make_unique<LBossRazerReady>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSRAZER, std::make_unique<LBossRazer>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSTHICKRAZER, std::make_unique<LBossThickRazer>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSMOVE, std::make_unique<LBossMove>(this)));
    /*
    m_pActionList.insert(std::make_pair(State::TRACE, std::make_unique<LMonsterTrace>(this)));
    m_pActionList.insert(std::make_pair(State::GOHOME, std::make_unique<LMonsterGoHome>(this)));
    m_pActionList.insert(std::make_pair(State::ATTACK, std::make_unique<LMonsterAttack>(this)));*/

    m_pAction = m_pActionList.find(State::BOSSIDLE)->second.get();
    m_CurrentState = State::BOSSIDLE;
}

void LBoss::SetTransition(Event inputEvent)
{
    m_CurrentState = m_pFsm->StateTransition(m_CurrentState, inputEvent);
    m_pAction = m_pActionList.find(m_CurrentState)->second.get();
}

State LBoss::GetState()
{
    return m_CurrentState;
}

void LBoss::Move()
{
}

void LBoss::Process(LPlaneObj* player)
{
    // 상태 보기용 AddText
    /*std::wstring textState = L"CurrentState : ";
    textState += m_TextList.find(m_CurrentState)->second;
    LWrite::GetInstance().AddText(textState, 0.0f, 50.0f, { 1.0f, 1.0f, 1.0f, 1.0f });*/

    m_pAction->Process(player);
}

bool LBoss::Init()
{
    m_AnimationList.insert(std::make_pair(State::BOSSIDLE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSIDLE)->second->SetUVAnimation(L"../../res/boss/bossidle4.png", 4, 1.0f);
    m_AnimationList.insert(std::make_pair(State::BOSSMOVE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSMOVE)->second->SetUVAnimation(L"../../res/boss/bossidle4.png", 4, 1.0f);
    m_AnimationList.insert(std::make_pair(State::BOSSSTAR, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSSTAR)->second->SetUVAnimation(L"../../res/boss/starattack5.png", 5, 1.0f);
    m_AnimationList.insert(std::make_pair(State::BOSSRAZERREADY, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSRAZERREADY)->second->SetUVAnimation(L"../../res/boss/razerready8.png", 8, 0.8f);
    m_AnimationList.insert(std::make_pair(State::BOSSRAZER, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSRAZER)->second->SetUVAnimation(L"../../res/boss/razerattack20.png", 20, 2.0f);
    m_AnimationList.insert(std::make_pair(State::BOSSTHICKRAZER, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BOSSTHICKRAZER)->second->SetUVAnimation(L"../../res/boss/thickrazerattack20.png", 20, 2.0f);
    
    m_vPosition = m_StartPos;

    m_LifeCounter = std::make_unique<LLife>();
    m_LifeCounter->Set(m_pDevice, m_pImmediateContext);
    m_LifeCounter->SetScale({ 50.0f, 50.0f, 1.0f });
    m_LifeCounter->SetPos({ 400.0f - 50.0f, -300.0f + 25.0f, 1.0f });
    m_LifeCounter->Create(L"../../res/PVShader.hlsl", L"../../res/boss/bosslifecount7.png");
    m_LifeCounter->SetUVAnimation(7, 1.0f);

    m_DamagedEffect = std::make_unique<LSpriteUVObj>();
    m_DamagedEffect->Set(m_pDevice, m_pImmediateContext);
    m_DamagedEffect->SetScale({ 54.0f, 54.0f, 1.0f });
    m_DamagedEffect->SetPos(m_vPosition);
    m_DamagedEffect->Create(L"../../res/PVShader.hlsl", L"../../res/effect/damaged1.png");
    m_DamagedEffect->SetUVAnimation(1, 1.0f);

    return true;
}

bool LBoss::Frame()
{
    // 몬스터 렉트 갱신
    SetBox(m_vPosition, 108.0f, 108.0f, 1.0f);
    m_DamagedEffect->SetBox(m_vPosition);
    // 몬스터 행렬 갱신
    LMatrix matScale, matRotation, matTranslate;
    matScale.Scale(m_vScale);
    matRotation.ZRotate(m_vRotation.z);
    matTranslate.Translation(m_vPosition);
    m_matWorld = matScale * matRotation * matTranslate;

    // 몬스터 애니메이션 갱신
    auto Animationit = m_AnimationList.find(m_CurrentState);

    if (Animationit == m_AnimationList.end())
    {
        MessageBoxA(NULL, "Animation iterator Error", "Error Box", MB_OK);
        return false;
    }

    m_Tex = Animationit->second->m_AnimationTexture;
    Animationit->second->Frame();

    // 플레이어의 앞뒤 애니메이션 출력   
    if (m_IsFront)
    {
        Animationit->second->SetUVPosition(m_VertexList);
    }
    else
    {
        Animationit->second->SetUVPositionReverse(m_VertexList);
    }

    // 맵밖으로 나가지 않게
    float halfMapX = 400;
    float halfMapY = 300;
    float halfPlayerX = m_Box.m_fWidth * 0.5f;
    float halfPlayerY = m_Box.m_fHeight * 0.5f;

    // 몬스터 좌우 끝 위치에 도달하면 반대쪽으로 이동
    /*if (m_vPosition.x >= (m_StartPos.x + m_moveDistance))
    {
        m_RightEnd = true;
        m_LeftEnd = false;
    }*/

    

    /*if (m_vPosition.x <= (m_StartPos.x - m_moveDistance))
    {
        m_LeftEnd = true;
        m_RightEnd = false;
    }*/

    /*if (m_isFloor)
    {
        if (m_vPosition.y < -halfMapY + halfPlayerY + m_FloorBox.m_fHeight)
        {
            m_vPosition.y = -halfMapY + halfPlayerY + m_FloorBox.m_fHeight;
        }
    }*/

    if (m_vPosition.x < -halfMapX + halfPlayerX)
    {
        m_vPosition.x = -halfMapX + halfPlayerX;
    }

    if (m_vPosition.y < -halfMapY + halfPlayerY)
    {
        m_vPosition.y = -halfMapY + halfPlayerY;
    }

    if (m_vPosition.x > halfMapX - halfPlayerX)
    {
        m_vPosition.x = halfMapX - halfPlayerX;
    }

    if (m_vPosition.y > halfMapY - halfPlayerY)
    {
        m_vPosition.y = halfMapY - halfPlayerY;
    }


    return true;
}

bool LBoss::Render()
{
    PreRender();
    LGlobal::g_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
    PostRender();

    return true;
}

bool LBoss::Release()
{
    return true;
}


LBoss::LBoss() {}
LBoss::~LBoss() {}


