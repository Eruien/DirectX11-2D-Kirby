#include "LBossIdle.h"

bool LBossIdle::Init()
{
	return true;
}

void LBossIdle::Process(LPlaneObj* player)
{
	m_UseStarTime += g_fSPF;
	m_UseRazerTime += g_fSPF;
	
	if (m_UseStarTime >= m_StarCoolTime)
	{
		m_pOwner->ClearThreeStar();
		m_UseStar = true;
	}

	if (m_UseRazerTime >= m_RazerCoolTime)
	{
		m_pOwner->ClearThreeStar();
		m_pOwner->ClearRazer();
		m_UseRazer = true;
	}

	if (m_UseRazer)
	{
		m_pOwner->SetTransition(Event::BOSSRAZERATTACK);
		m_UseRazer = false;
		m_UseRazerTime = 0;
		return;
	}

	if (m_UseStar)
	{
		m_pOwner->SetTransition(Event::BOSSSTARTMOVE);
		m_UseStar = false;
		m_UseStarTime = 0;
		return;
	}
}

LBossIdle::LBossIdle(LBoss* parent) : BossState(parent) {}
LBossIdle::~LBossIdle() {}