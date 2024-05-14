#include "LPlayer.h"
#include "LWrite.h"
#include "LIdleAction.h"
#include "LWalkAction.h"
#include "LGlobal.h"
#include "LCrouch.h"
#include "LSlide.h"
#include "LRunAction.h"
#include "LAirInHale.h"
#include "LAirOutHale.h"
#include "LFly.h"
#include "LFall.h"
#include "LFlapping.h"
#include "LFirstInHale.h"
#include "LSecondInHale.h"
#include "LFatIdle.h"
#include "LFatMode.h"
#include "LModeChange.h"
#include "LTakeDamage.h"
#include "LDeadAction.h"
#include "LBeamIdleAction.h"
#include "LBeamWalkAction.h"
#include "LBeamRunAction.h"
#include "LBeamCrouch.h"
#include "LBeamSlide.h"
#include "LBeamFly.h"
#include "LBeamFlapping.h"
#include "LBeamAirInHale.h"
#include "LBeamAirOutHale.h"
#include "LBeamFall.h"
#include "LBeamAttack.h"
// Angel
#include "LAngelAttack.h"
#include "LAngelCrouch.h"
#include "LAngelIdleAction.h"
#include "LAngelRunAction.h"
#include "LAngelSlide.h"
#include "LAngelSlide.h"
#include "LAngelWalkAction.h"
#include "LAngelFall.h"
#include "LAngelFlapping.h"
#include "LAngelFly.h"

bool LPlayer::CreateVertexBuffer()
{
    //벡터로 변경
    m_VertexList.resize(6);
    m_VertexList[0].p.x = -1.0f; m_VertexList[0].p.y = 1.0f;  m_VertexList[0].p.z = 0.0f;
    m_VertexList[1].p.x = 1.0f;  m_VertexList[1].p.y = 1.0f;  m_VertexList[1].p.z = 0.0f;
    m_VertexList[2].p.x = -1.0f; m_VertexList[2].p.y = -1.0f; m_VertexList[2].p.z = 0.0f;

    m_VertexList[3].p.x = -1.0f; m_VertexList[3].p.y = -1.0f; m_VertexList[3].p.z = 0.0f;
    m_VertexList[4].p.x = 1.0f;  m_VertexList[4].p.y = 1.0f;  m_VertexList[4].p.z = 0.0f;
    m_VertexList[5].p.x = 1.0f;  m_VertexList[5].p.y = -1.0f; m_VertexList[5].p.z = 0.0f;

    m_VertexList[0].t.x = 0.0f;   m_VertexList[0].t.y = 0.0f;
    m_VertexList[1].t.x = 1.0f;  m_VertexList[1].t.y = 0.0f;
    m_VertexList[2].t.x = 0.0f;   m_VertexList[2].t.y = 1.0f;

    m_VertexList[3].t.x = 0.0f;   m_VertexList[3].t.y = 1.0f;
    m_VertexList[4].t.x = 1.0f;  m_VertexList[4].t.y = 0.0f;
    m_VertexList[5].t.x = 1.0f;  m_VertexList[5].t.y = 1.0f;

    // 버퍼에 대한 설명서
    D3D11_BUFFER_DESC bufferDesc = { 0, };
    bufferDesc.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initialData = { 0, };
    initialData.pSysMem = &m_VertexList.at(0);

    HRESULT hr = m_pDevice->CreateBuffer(
        &bufferDesc,
        &initialData,
        &m_pVertexBuffer);

    if (FAILED(hr))
    {
        MessageBoxA(NULL, "Create Buffer Error", "Error Box", MB_OK);
        return false;
    }

    return true;
}

void LPlayer::FSM(FSMType fsmType)
{
    auto iter = LFSMMgr::GetInstance().m_map.find(fsmType);

    if (LFSMMgr::GetInstance().m_map.end() == iter)
    {
        MessageBoxA(NULL, "FSMType Error", "Error Box", MB_OK);
        return;
    }

    m_pFsm = iter->second.get();

    m_pActionList.insert(std::make_pair(State::IDLE, std::make_unique<LIdleAction>(this)));
    m_pActionList.insert(std::make_pair(State::WALK, std::make_unique<LWalkAction>(this)));
    m_pActionList.insert(std::make_pair(State::RUN, std::make_unique<LRunAction>(this)));
    m_pActionList.insert(std::make_pair(State::CROUCH, std::make_unique<LCrouch>(this)));
    m_pActionList.insert(std::make_pair(State::SILDE, std::make_unique<LSlide>(this)));
    m_pActionList.insert(std::make_pair(State::AIRINHALE, std::make_unique<LAirInHale>(this)));
    m_pActionList.insert(std::make_pair(State::AIROUTHALE, std::make_unique<LAirOutHale>(this)));
    m_pActionList.insert(std::make_pair(State::FLY, std::make_unique<LFly>(this)));
    m_pActionList.insert(std::make_pair(State::FALL, std::make_unique<LFall>(this)));
    m_pActionList.insert(std::make_pair(State::FLAPPING, std::make_unique<LFlapping>(this)));
    m_pActionList.insert(std::make_pair(State::FIRSTINHALE, std::make_unique<LFirstInHale>(this)));
    m_pActionList.insert(std::make_pair(State::SECONDINHALE, std::make_unique<LSecondInHale>(this)));
    m_pActionList.insert(std::make_pair(State::FATIDLE, std::make_unique<LFatIdle>(this)));
    m_pActionList.insert(std::make_pair(State::FATMODE, std::make_unique<LFatMode>(this)));
    m_pActionList.insert(std::make_pair(State::MODECHANGE, std::make_unique<LModeChange>(this)));
    m_pActionList.insert(std::make_pair(State::TAKEDAMAGE, std::make_unique<LTakeDamage>(this)));
    m_pActionList.insert(std::make_pair(State::USERDEAD, std::make_unique<LDeadAction>(this)));

    m_pActionList.insert(std::make_pair(State::BEAMIDLE, std::make_unique<LBeamIdleAction>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMWALK, std::make_unique<LBeamWalkAction>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMRUN, std::make_unique<LBeamRunAction>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMCROUCH, std::make_unique<LBeamCrouch>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMSILDE, std::make_unique<LBeamSlide>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMFLY, std::make_unique<LBeamFly>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMFLAPPING, std::make_unique<LBeamFlapping>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMAIRINHALE, std::make_unique<LBeamAirInHale>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMAIROUTHALE, std::make_unique<LBeamAirOutHale>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMFALL, std::make_unique<LBeamFall>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMATTACK, std::make_unique<LBeamAttack>(this)));

    m_pActionList.insert(std::make_pair(State::ANGELIDLE, std::make_unique<LBeamIdleAction>(this)));
    m_pActionList.insert(std::make_pair(State::ANGELWALK, std::make_unique<LBeamWalkAction>(this)));
    m_pActionList.insert(std::make_pair(State::ANGELRUN, std::make_unique<LBeamRunAction>(this)));
    m_pActionList.insert(std::make_pair(State::ANGELCROUCH, std::make_unique<LBeamCrouch>(this)));
    m_pActionList.insert(std::make_pair(State::ANGELSILDE, std::make_unique<LBeamSlide>(this)));
   /* m_pActionList.insert(std::make_pair(State::BEAMFLY, std::make_unique<LBeamFly>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMFLAPPING, std::make_unique<LBeamFlapping>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMAIRINHALE, std::make_unique<LBeamAirInHale>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMAIROUTHALE, std::make_unique<LBeamAirOutHale>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMFALL, std::make_unique<LBeamFall>(this)));
    m_pActionList.insert(std::make_pair(State::BEAMATTACK, std::make_unique<LBeamAttack>(this)));*/
   
    m_pAction = m_pActionList.find(State::IDLE)->second.get();
    m_CurrentState = State::IDLE;
}

void LPlayer::SetTransition(Event inputEvent)
{
    m_CurrentState = m_pFsm->StateTransition(m_CurrentState, inputEvent);
    m_AnimationList[m_CurrentState]->m_AnimationIndex = 0;
    m_pAction = m_pActionList.find(m_CurrentState)->second.get();
}

State LPlayer::GetState()
{
    return m_CurrentState;
}

void LPlayer::SetCollisionBoss(LPlaneObj* pBoss)
{
    m_pBoss = pBoss;
}

LPlaneObj* LPlayer::GetCollisionBoss()
{
    return m_pBoss;
}

void LPlayer::SetCollisionMonster(LPlaneObj* pMonster)
{
    m_pMonster = pMonster;
}

LPlaneObj* LPlayer::GetCollisionMonster()
{
    return m_pMonster;
}

void LPlayer::Process()
{
    // 상태 보기용 AddText
    std::wstring textState = L"CurrentState : ";
    textState += m_TextList.find(m_CurrentState)->second;
    //LWrite::GetInstance().AddText(textState, 0.0f, 50.0f, { 1.0f, 1.0f, 1.0f, 1.0f });

    m_pAction->Process();
}

bool LPlayer::Init()
{
    m_AnimationList.insert(std::make_pair(State::WALK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::WALK)->second->SetUVAnimation(L"../../res/walk10.png", 10, 1.0f);

    m_AnimationList.insert(std::make_pair(State::IDLE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::IDLE)->second->SetUVAnimation(L"../../res/idle2.png", 2, 1.0f);

    m_AnimationList.insert(std::make_pair(State::RUN, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::RUN)->second->SetUVAnimation(L"../../res/run8.png", 8, 0.5f);

    m_AnimationList.insert(std::make_pair(State::CROUCH, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::CROUCH)->second->SetUVAnimation(L"../../res/crouch1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::SILDE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::SILDE)->second->SetUVAnimation(L"../../res/slide1.png", 1, 0.8f);

    m_AnimationList.insert(std::make_pair(State::AIRINHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::AIRINHALE)->second->SetUVAnimation(L"../../res/airinhale5.png", 5, 0.15f);

    m_AnimationList.insert(std::make_pair(State::AIROUTHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::AIROUTHALE)->second->SetUVAnimation(L"../../res/airouthale3.png", 3, 0.15f);

    m_AnimationList.insert(std::make_pair(State::FALL, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FALL)->second->SetUVAnimation(L"../../res/fall14.png", 14, 1.0f);

    m_AnimationList.insert(std::make_pair(State::FLAPPING, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FLAPPING)->second->SetUVAnimation(L"../../res/flapping5.png", 5, 1.0f);

    m_AnimationList.insert(std::make_pair(State::FLY, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FLY)->second->SetUVAnimation(L"../../res/fly1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::FIRSTINHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FIRSTINHALE)->second->SetUVAnimation(L"../../res/firstinhale11.png", 11, 1.1f);

    m_AnimationList.insert(std::make_pair(State::SECONDINHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::SECONDINHALE)->second->SetUVAnimation(L"../../res/secondinhale14.png", 14, 1.4f);

    m_AnimationList.insert(std::make_pair(State::FATIDLE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FATIDLE)->second->SetUVAnimation(L"../../res/fatidle1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::FATMODE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::FATMODE)->second->SetUVAnimation(L"../../res/fatmode15.png", 15, 1.5f);

    m_AnimationList.insert(std::make_pair(State::MODECHANGE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::MODECHANGE)->second->SetUVAnimation(L"../../res/modechange1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::TAKEDAMAGE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::TAKEDAMAGE)->second->SetUVAnimation(L"../../res/takedamage5.png", 5, 1.0f);

    m_AnimationList.insert(std::make_pair(State::USERDEAD, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::USERDEAD)->second->SetUVAnimation(L"../../res/userdead16.png", 16, 2.0f);

    // 여기서부터 beam
    m_AnimationList.insert(std::make_pair(State::BEAMIDLE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMIDLE)->second->SetUVAnimation(L"../../res/beam/beamidle2.png", 2, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMWALK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMWALK)->second->SetUVAnimation(L"../../res/beam/beamwalk12.png", 12, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMRUN, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMRUN)->second->SetUVAnimation(L"../../res/beam/beamrun8.png", 8, 0.5f);

    m_AnimationList.insert(std::make_pair(State::BEAMCROUCH, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMCROUCH)->second->SetUVAnimation(L"../../res/beam/beamcrouch1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMSILDE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMSILDE)->second->SetUVAnimation(L"../../res/beam/beamslide1.png", 1, 0.8f);

    m_AnimationList.insert(std::make_pair(State::BEAMAIRINHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMAIRINHALE)->second->SetUVAnimation(L"../../res/beam/beamairinhale3.png", 3, 0.15f);

    m_AnimationList.insert(std::make_pair(State::BEAMAIROUTHALE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMAIROUTHALE)->second->SetUVAnimation(L"../../res/beam/beamairouthale2.png", 2, 0.15f);

    m_AnimationList.insert(std::make_pair(State::BEAMFALL, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMFALL)->second->SetUVAnimation(L"../../res/beam/beamfall14.png", 14, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMFLAPPING, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMFLAPPING)->second->SetUVAnimation(L"../../res/beam/beamflapping8.png", 8, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMFLY, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMFLY)->second->SetUVAnimation(L"../../res/beam/beamfly1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::BEAMATTACK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::BEAMATTACK)->second->SetUVAnimation(L"../../res/beam/beamidle2.png", 2, 1.0f);

    // 여기서부터 angel
    m_AnimationList.insert(std::make_pair(State::ANGELIDLE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELIDLE)->second->SetUVAnimation(L"../../res/angel/angelidle2.png", 2, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELWALK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELWALK)->second->SetUVAnimation(L"../../res/angel/angelwalk9.png", 9, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELRUN, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELRUN)->second->SetUVAnimation(L"../../res/angel/angelrun8.png", 8, 0.5f);

    m_AnimationList.insert(std::make_pair(State::ANGELCROUCH, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELCROUCH)->second->SetUVAnimation(L"../../res/angel/angelcrouch1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELSILDE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELSILDE)->second->SetUVAnimation(L"../../res/angel/angelslide1.png", 1, 0.8f);

   /* m_AnimationList.insert(std::make_pair(State::ANGELFALL, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELFALL)->second->SetUVAnimation(L"../../res/beam/beamfall14.png", 14, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELFLAPPING, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELFLAPPING)->second->SetUVAnimation(L"../../res/beam/beamflapping8.png", 8, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELFLY, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELFLY)->second->SetUVAnimation(L"../../res/beam/beamfly1.png", 1, 1.0f);

    m_AnimationList.insert(std::make_pair(State::ANGELATTACK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ANGELATTACK)->second->SetUVAnimation(L"../../res/beam/beamidle2.png", 2, 1.0f);*/

    m_TextList.insert(std::make_pair(State::AIRINHALE, L"AirINHale"));
    m_TextList.insert(std::make_pair(State::AIROUTHALE, L"AirOutHale"));
    m_TextList.insert(std::make_pair(State::CROUCH, L"Crouch"));
    m_TextList.insert(std::make_pair(State::FALL, L"fall"));
    m_TextList.insert(std::make_pair(State::FLAPPING, L"flapping"));
    m_TextList.insert(std::make_pair(State::FLY, L"fly"));
    m_TextList.insert(std::make_pair(State::IDLE, L"idle"));
    m_TextList.insert(std::make_pair(State::NONE, L"none"));
    m_TextList.insert(std::make_pair(State::RUN, L"run"));
    m_TextList.insert(std::make_pair(State::SILDE, L"slide"));
    m_TextList.insert(std::make_pair(State::WALK, L"walk"));
    m_TextList.insert(std::make_pair(State::FIRSTINHALE, L"firstInHale"));
    m_TextList.insert(std::make_pair(State::SECONDINHALE, L"secondInHale"));
    m_TextList.insert(std::make_pair(State::FATIDLE, L"FatIdle"));
    m_TextList.insert(std::make_pair(State::FATMODE, L"FatMode"));
    m_TextList.insert(std::make_pair(State::MODECHANGE, L"modechange"));
    m_TextList.insert(std::make_pair(State::TAKEDAMAGE, L"takedamage"));
    m_TextList.insert(std::make_pair(State::USERDEAD, L"userdead"));

    m_TextList.insert(std::make_pair(State::BEAMIDLE, L"beamIdle"));
    m_TextList.insert(std::make_pair(State::BEAMWALK, L"beamwalk"));
    m_TextList.insert(std::make_pair(State::BEAMRUN, L"beamrun"));
    m_TextList.insert(std::make_pair(State::BEAMCROUCH, L"beamcrouch"));
    m_TextList.insert(std::make_pair(State::BEAMSILDE, L"beamslide"));
    m_TextList.insert(std::make_pair(State::BEAMFLY, L"beamfly"));
    m_TextList.insert(std::make_pair(State::BEAMFLAPPING, L"beamflapping"));
    m_TextList.insert(std::make_pair(State::BEAMAIRINHALE, L"beamairinhale"));
    m_TextList.insert(std::make_pair(State::BEAMAIROUTHALE, L"beamairouthale"));
    m_TextList.insert(std::make_pair(State::BEAMFALL, L"beamfall"));
    m_TextList.insert(std::make_pair(State::BEAMATTACK, L"beamattack"));

    m_TextList.insert(std::make_pair(State::ANGELIDLE, L"angelidle"));
    m_TextList.insert(std::make_pair(State::ANGELWALK, L"angelwalk"));
    m_TextList.insert(std::make_pair(State::ANGELRUN, L"angelrun"));
    m_TextList.insert(std::make_pair(State::ANGELCROUCH, L"angelcrouch"));
    m_TextList.insert(std::make_pair(State::ANGELSILDE, L"angelslide"));
  
    m_pEffect = std::make_unique<LEffect>();
    m_pEffect->SetEffect(this, L"../../res/PVShader.hlsl", L"../../res/none1.png", 100.0f, 24.0f);

    m_pEffect->m_AnimationList.insert(std::make_pair(State::FIRSTINHALE, std::make_unique<LAnimation>()));
    m_pEffect->m_AnimationList.find(State::FIRSTINHALE)->second->SetUVAnimation(L"../../res/inhaleeffect12.png", 12, 1.1f);

    m_pEffect->m_AnimationList.insert(std::make_pair(State::SECONDINHALE, std::make_unique<LAnimation>()));
    m_pEffect->m_AnimationList.find(State::SECONDINHALE)->second->SetUVAnimation(L"../../res/inhaleeffect12.png", 12, 1.1f);

    m_pEffect->m_AnimationList.insert(std::make_pair(State::NONE, std::make_unique<LAnimation>()));
    m_pEffect->m_AnimationList.find(State::NONE)->second->SetUVAnimation(L"../../res/none1.png", 1, 1.0f);

    m_pEffect->m_AnimationList.insert(std::make_pair(State::BEAMATTACK, std::make_unique<LAnimation>()));
    m_pEffect->m_AnimationList.find(State::BEAMATTACK)->second->SetUVAnimation(L"../../res/beam/beamattack11.png", 11, 1.5f);

    m_LifeCounter = std::make_unique<LLife>();
    m_LifeCounter->Set(m_pDevice, m_pImmediateContext);
    m_LifeCounter->SetScale({ 50.0f, 50.0f, 1.0f });
    m_LifeCounter->SetPos({ m_vPosition.x - 400 + 50, m_vPosition.y - 300 + 25, 1.0f });
    m_LifeCounter->Create(L"../../res/PVShader.hlsl", L"../../res/lifecount7.png");
    m_LifeCounter->SetUVAnimation(7, 1.0f);
    return true;
}

bool LPlayer::Frame()
{
    // 플레이어 위치 갱신
    SetBox(m_vPosition, 48.0f, 36.0f, 1.0f);
    m_LifeCounter->m_vPosition.x = LGlobal::g_pMainCamera->m_vCameraPos.x - (g_WindowWidth * 0.5f) + m_LifeCounter->m_vScale.x;
    // 플레이어의 행렬 갱신
    LMatrix matScale, matRotation, matTranslation;
    matScale.Scale(m_vScale);
    matRotation.ZRotate(m_vRotation.z);
    matTranslation.Translation(m_vPosition);
    m_matWorld = matScale * matRotation * matTranslation;

    auto Animationit = m_AnimationList.find(m_CurrentState);

    if (Animationit == m_AnimationList.end())
    {
        MessageBoxA(NULL, "Animation iterator Error", "Error Box", MB_OK);
        return false;
    }

    m_Tex = Animationit->second->m_AnimationTexture;
    Animationit->second->Frame();
   
    m_pEffect->Frame();
    //m_pBeamEffect->Frame();

    // RunAction 제어
    if (m_StartTimeLeft)
    {
        m_RunTimeLeft += g_fSPF;
        if (m_RunTimeLeft < 0.3f)
        {
            m_IsRunLeft = true;
        }
        else
        {
            m_IsRunLeft = false;
        }
    }

    if (m_StartTimeRight)
    {
        m_RunTimeRight += g_fSPF;
        if (m_RunTimeRight < 0.3f)
        {
            m_IsRunRight = true;
        }
        else
        {
            m_IsRunRight = false;
        }
    }

    // 플레이어의 앞뒤 제어   
    if (m_IsFront)
    {
        Animationit->second->SetUVPosition(m_VertexList);
    }
    else
    {
        Animationit->second->SetUVPositionReverse(m_VertexList);
    }

    // 맵밖으로 나가지 않게
    float halfPlayerX = m_Box.m_fWidth * 0.5f;
    float halfPlayerY = m_Box.m_fHeight * 0.5f;

    if (m_isFloor)
    {
        if (m_vPosition.y < -m_HalfMapY + halfPlayerY + m_FloorBox.m_fHeight)
        {
            m_vPosition.y = -m_HalfMapY + halfPlayerY + m_FloorBox.m_fHeight;
        }
    }

    if (m_vPosition.x < -m_HalfMapX + halfPlayerX)
    {
        m_vPosition.x = -m_HalfMapX + halfPlayerX;
    }

    if (m_vPosition.y < -m_HalfMapY + halfPlayerY)
    {
        m_vPosition.y = -m_HalfMapY + halfPlayerY;
    }

    if (m_vPosition.x > m_HalfMapX - halfPlayerX)
    {
        m_vPosition.x = m_HalfMapX - halfPlayerX;
    }

   if (m_vPosition.y > m_HalfMapY - halfPlayerY)
   {
       m_vPosition.y = m_HalfMapY - halfPlayerY;
   }

    return true;
}

bool LPlayer::Render()
{
    PreRender();
    LGlobal::g_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
    PostRender();

    m_pEffect->Render();

    
    //m_pBeamEffect->Render();

    return true;
}

bool LPlayer::Release()
{
    return true;
}

LPlayer::LPlayer() {}
LPlayer::~LPlayer() {}

// Effect

void LEffect::SetEffect(LPlayer* pPlayer, std::wstring shaderfilePath, std::wstring texfilePath, float widthScale, float heightScale)
{
    m_pPlayer = pPlayer;
    m_vPosition = m_pPlayer->m_vPosition;
   
    Set(m_pPlayer->m_pDevice, m_pPlayer->m_pImmediateContext);
    SetScale(LVector(widthScale, heightScale, 1.0f));
    SetBox(m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);
    Create(shaderfilePath.c_str(), texfilePath.c_str());
    m_EffectDistance = (m_pPlayer->m_Box.m_fWidth * 0.5f) + (m_Box.m_fWidth * 0.5f) - 8;
}

bool LEffect::Init()
{
    return true;
}

bool LEffect::Frame()
{
    SetBox(m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);

    LPlaneObj::Frame();

    //auto Animationit = m_AnimationList.find(State::BEAMATTACK);

    ////if (Animationit == m_AnimationList.end())
    ////{
    ////    //MessageBoxA(NULL, "Animation iterator Error", "Error Box", MB_OK);
    ////    return false;
    ////}

    //m_Tex = Animationit->second->m_AnimationTexture;
    //Animationit->second->Frame();

    auto Animationit = m_AnimationList.find(m_pPlayer->m_CurrentState);

    if (Animationit != m_AnimationList.end())
    {
        m_Tex = Animationit->second->m_AnimationTexture;
        Animationit->second->Frame();
    }

    if (Animationit == m_AnimationList.end())
    {
        if (m_pPlayer->m_IsFront)
        {
            m_vPosition.x = m_pPlayer->m_vPosition.x + m_EffectDistance;
            m_vPosition.y = m_pPlayer->m_vPosition.y;
        }
        else
        {
            m_vPosition.x = m_pPlayer->m_vPosition.x - m_EffectDistance;
            m_vPosition.y = m_pPlayer->m_vPosition.y;
        }
        auto nonIter = m_AnimationList.find(State::NONE);
        m_Tex = nonIter->second->m_AnimationTexture;
        nonIter->second->Frame();
    }

    if (Animationit != m_AnimationList.end())
    {
        if (m_pPlayer->m_IsFront)
        {
            m_vPosition.x = m_pPlayer->m_vPosition.x + m_EffectDistance;
            m_vPosition.y = m_pPlayer->m_vPosition.y;
            Animationit->second->SetUVPosition(m_VertexList);
        }
        else
        {
            m_vPosition.x = m_pPlayer->m_vPosition.x - m_EffectDistance;
            m_vPosition.y = m_pPlayer->m_vPosition.y;
            Animationit->second->SetUVPositionReverse(m_VertexList);
        }
    }
  
    return true;
}

bool LEffect::Render()
{
    PreRender();
    LGlobal::g_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
    PostRender();
    return true;
}
