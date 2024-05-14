#include "LMonsterTrace.h"

bool LMonsterTrace::Init()
{
	return true;
}

void LMonsterTrace::Process(LPlaneObj* player)
{
	if (!m_pOwner->m_isFloor)
	{
		m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;
	}

	LVector dir = m_pOwner->m_Box.m_Center - player->m_Box.m_Center;

	if (fabs(dir.x) <= m_AttackRange)
	{
		if (fabs(dir.y) <= m_AttackRange)
		{
			m_pOwner->SetTransition(Event::ATTACKPOS);
			return;
		}
	}

	if (m_pOwner->m_vPosition.x < player->m_vPosition.x)
	{
		m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
		m_pOwner->m_IsFront = false;
	}

	if (m_pOwner->m_vPosition.x > player->m_vPosition.x)
	{
		m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
		m_pOwner->m_IsFront = true;
	}

	

	dir = m_pOwner->m_Box.m_Center - player->m_Box.m_Center;

	if (fabs(dir.x) <= m_TraceRange)
	{
		if (fabs(dir.y) <= m_TraceRange)
		{
			return;
		}
	}

	m_pOwner->SetTransition(Event::LOSTTARGET);
}

LMonsterTrace::LMonsterTrace(LMonster* parent, float actionTimeStart, float actionTimeEnd)
	: MonsterState(parent, actionTimeStart, actionTimeEnd) {}
LMonsterTrace::~LMonsterTrace() {}