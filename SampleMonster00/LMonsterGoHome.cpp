#include "LMonsterGoHome.h"

bool LMonsterGoHome::Init()
{
	return true;
}

void LMonsterGoHome::Process(LPlaneObj* player)
{
	if (!m_pOwner->m_isFloor)
	{
		m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;
	}

	LVector dir = m_pOwner->m_StartPos - m_pOwner->m_Box.m_Center;
	
	m_pOwner->m_vPosition.x += m_pOwner->m_Speed * dir.NormalVector().x * g_fSPF;

	if (dir.NormalVector().x < 0)
	{
		m_pOwner->m_IsFront = true;
	}
	else
	{
		m_pOwner->m_IsFront = false;
	}

	if (fabs(dir.x) <= m_HomeRange)
	{
		if (fabs(dir.x) <= m_HomeRange)
		{
			m_pOwner->SetTransition(Event::ARRIVESTARTPOS);
			return;
		}
	}

	dir = m_pOwner->m_Box.m_Center - player->m_Box.m_Center;

	if (fabs(dir.x) <= m_findTargetRange)
	{
		if (fabs(dir.y) <= m_findTargetRange)
		{
			m_pOwner->SetTransition(Event::FINDTARGET);
			return;
		}
	}
}

LMonsterGoHome::LMonsterGoHome(LMonster* parent, float actionTimeStart, float actionTimeEnd)
	: MonsterState(parent, actionTimeStart, actionTimeEnd) {}
LMonsterGoHome::~LMonsterGoHome() {}