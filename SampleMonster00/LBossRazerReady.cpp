#include "LBossRazerReady.h"

bool LBossRazerReady::Init()
{
	return true;
}

void LBossRazerReady::Process(LPlaneObj* player)
{
	// boss size 144
	m_pOwner->m_vPosition.x = -m_pOwner->m_HalfMapsizeX + m_pOwner->m_vScale.x;
	m_pOwner->m_vPosition.y = -m_pOwner->m_HalfMapsizeY + m_pOwner->m_vScale.y + 64.0f;
	m_pOwner->m_IsFront = true;

	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex == 
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{	
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0.0f;
		m_pOwner->SetTransition(Event::BOSSENDPATTERN);
		return;
	}
}

LBossRazerReady::LBossRazerReady(LBoss* parent) : BossState(parent) {}
LBossRazerReady::~LBossRazerReady() {}