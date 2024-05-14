#include "LScene.h"
#include "LGlobal.h"
#include "LMainScene.h"
#include "LGameScene.h"
#include "LBossScene.h"
#include "LEndScene.h"

void LScene::SceneSet(std::shared_ptr<LCamera> MainCamera, ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
    m_pMainCamera = MainCamera;
    m_pDevice = pDevice;
    m_pImmediateContext = pImmediateContext;
}

void LScene::FSM(FSMType fsmType)
{
    auto iter = LFSMMgr::GetInstance().m_map.find(fsmType);

    if (LFSMMgr::GetInstance().m_map.end() == iter)
    {
        MessageBoxA(NULL, "FSMType Error", "Error Box", MB_OK);
        return;
    }

    m_pFsm = iter->second.get();

    m_pActionList.insert(std::make_pair(State::MAINSCENE, std::make_unique<LMainScene>(this)));
    m_pActionList.insert(std::make_pair(State::GAMESCENE, std::make_unique<LGameScene>(this)));
    m_pActionList.insert(std::make_pair(State::BOSSSCENE, std::make_unique<LBossScene>(this)));
    m_pActionList.insert(std::make_pair(State::ENDSCENE, std::make_unique<LEndScene>(this)));

    /*m_pActionList.insert(std::make_pair(State::MOVE, std::make_unique<LMonsterMove>(this)));
    m_pActionList.insert(std::make_pair(State::TRACE, std::make_unique<LMonsterTrace>(this)));
    m_pActionList.insert(std::make_pair(State::GOHOME, std::make_unique<LMonsterGoHome>(this)));
    m_pActionList.insert(std::make_pair(State::ATTACK, std::make_unique<LMonsterAttack>(this)));*/

    m_pAction = m_pActionList.find(State::MAINSCENE)->second.get();
    m_CurrentState = State::MAINSCENE;
}

void LScene::SetTransition(Event inputEvent)
{
    m_CurrentState = m_pFsm->StateTransition(m_CurrentState, inputEvent);
    m_pAction = m_pActionList.find(m_CurrentState)->second.get();
}

State LScene::GetState()
{
    return m_CurrentState;
}

void LScene::Process()
{
    m_pAction->Process();
}

bool LScene::Init()
{
    m_pPlayer = new LPlayer;
    m_pPlayer->FSM(FSMType::Player);
    m_pPlayer->Set(m_pDevice, m_pImmediateContext);
    m_pPlayer->SetScale(LVector(24.0f, 24.0f, 1.0f));
    m_pPlayer->SetBox(m_pPlayer->m_vPosition, m_pPlayer->m_vScale.x * 2, m_pPlayer->m_vScale.y * 2, 1.0f);
    m_pPlayer->Create(L"../../res/PVShader.hlsl", L"../../res/airmove1.png");
    m_pPlayer->Init();
    return true;
}

bool LScene::Frame()
{
    
    return true;
}

bool LScene::Render()
{
    return true;
}

bool LScene::Release()
{
    return true;
}

LScene::LScene() {}
LScene::~LScene() {}


