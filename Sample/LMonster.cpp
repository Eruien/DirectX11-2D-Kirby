#include "LMonster.h"
#include "LGlobal.h"
#include "LMonsterMove.h"
#include "LMonsterTrace.h"
#include "LMonsterGoHome.h"
#include "LMonsterAttack.h"

void LMonster::FSM(FSMType fsmType)
{
	auto iter = LFSMMgr::GetInstance().m_map.find(fsmType);

	if (LFSMMgr::GetInstance().m_map.end() == iter)
	{
		MessageBoxA(NULL, "FSMType Error", "Error Box", MB_OK);
		return;
	}

	m_pFsm = iter->second.get();

	m_pActionList.insert(std::make_pair(State::MOVE, std::make_unique<LMonsterMove>(this)));
    m_pActionList.insert(std::make_pair(State::TRACE, std::make_unique<LMonsterTrace>(this)));
    m_pActionList.insert(std::make_pair(State::GOHOME, std::make_unique<LMonsterGoHome>(this)));
    m_pActionList.insert(std::make_pair(State::ATTACK, std::make_unique<LMonsterAttack>(this)));
   
	m_pAction = m_pActionList.find(State::MOVE)->second.get();
	m_CurrentState = State::MOVE;
}

void LMonster::SetTransition(Event inputEvent)
{
	m_CurrentState = m_pFsm->StateTransition(m_CurrentState, inputEvent);
	m_pAction = m_pActionList.find(m_CurrentState)->second.get();
}

State LMonster::GetState()
{
	return m_CurrentState;
}

void LMonster::Move()
{
}

void LMonster::Process(LPlaneObj* player)
{
	// 상태 보기용 AddText
	/*std::wstring textState = L"CurrentState : ";
	textState += m_TextList.find(m_CurrentState)->second;
	LWrite::GetInstance().AddText(textState, 0.0f, 50.0f, { 1.0f, 1.0f, 1.0f, 1.0f });*/

	m_pAction->Process(player);
}

bool LMonster::Init()
{
	m_AnimationList.insert(std::make_pair(State::MOVE, std::make_unique<LAnimation>()));
	m_AnimationList.find(State::MOVE)->second->SetUVAnimation(L"../../res/monster/move8.png", 8, 1.0f);
    m_AnimationList.insert(std::make_pair(State::TRACE, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::TRACE)->second->SetUVAnimation(L"../../res/monster/move8.png", 8, 1.0f);
    m_AnimationList.insert(std::make_pair(State::GOHOME, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::GOHOME)->second->SetUVAnimation(L"../../res/monster/move8.png", 8, 1.0f);
    m_AnimationList.insert(std::make_pair(State::ATTACK, std::make_unique<LAnimation>()));
    m_AnimationList.find(State::ATTACK)->second->SetUVAnimation(L"../../res/monster/attack5.png", 5, 2.0f);

	m_vPosition = m_StartPos;
	return true;
}

bool LMonster::Frame()
{
    // 몬스터 렉트 갱신
	SetBox(m_vPosition, 48.0f, 36.0f, 1.0f);

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
    float halfMapX = g_fMapSizeX;
    float halfMapY = g_fMapSizeY;
    float halfPlayerX = m_Box.m_fWidth * 0.5f;
    float halfPlayerY = m_Box.m_fHeight * 0.5f;

    // 몬스터 좌우 끝 위치에 도달하면 반대쪽으로 이동
    /*if (m_vPosition.x >= (m_StartPos.x + m_moveDistance))
    {
        m_RightEnd = true;
        m_LeftEnd = false;
    }*/

    if (m_vPosition.x >= halfMapX - halfPlayerX)
    {
        m_RightEnd = true;
        m_LeftEnd = false;
    }
   

    /*if (m_vPosition.x <= (m_StartPos.x - m_moveDistance))
    {
        m_LeftEnd = true;
        m_RightEnd = false;
    }*/

    if (m_vPosition.x <= -halfMapX + halfPlayerX)
    {
        m_LeftEnd = true;
        m_RightEnd = false;
    }

    if (m_isFloor)
    {
        if (m_vPosition.y < -halfMapY + halfPlayerY + m_FloorBox.m_fHeight)
        {
            m_vPosition.y = -halfMapY + halfPlayerY + m_FloorBox.m_fHeight;
        }
    }

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

bool LMonster::Render()
{
	PreRender();
	LGlobal::g_pImmediateContext->UpdateSubresource(
		m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
	PostRender();

	return true;
}

bool LMonster::Release()
{
	return true;
}


LMonster::LMonster() {}
LMonster::~LMonster() {}


