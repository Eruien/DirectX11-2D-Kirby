#include "LBossThickRazer.h"

bool LBossThickRazer::Init()
{
	return true;
}

void LBossThickRazer::Process(LPlaneObj* player)
{
	if (m_pOwner->m_RazerList.empty())
	{
		m_pOwner->CreateThickRazer();
	}

	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->ClearRazer();
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0.0f;
		m_pOwner->SetTransition(Event::BOSSENDPATTERN);
		return;
	}
}

LBossThickRazer::LBossThickRazer(LBoss* parent) : BossState(parent) {}
LBossThickRazer::~LBossThickRazer() {}