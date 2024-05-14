#include "LBossStar.h"

bool LBossStar::Init()
{
	return true;
}

void LBossStar::Process(LPlaneObj* player)
{
	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->CreateThreeStar();
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0;
		m_pOwner->SetTransition(Event::BOSSENDPATTERN);
		return;
	}
}

LBossStar::LBossStar(LBoss* parent) : BossState(parent) {}
LBossStar::~LBossStar() {}