#include "LMonsterMove.h"

bool LMonsterMove::Init()
{
	return true;
}

void LMonsterMove::Process(LPlaneObj* player)
{
	if (!m_pOwner->m_isFloor)
	{
		m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;
	}
	
	if (m_pOwner->m_vPosition.x < m_pOwner->m_StartPos.x - m_PatrolRange)
	{
		m_IsRightEnd = false;
	}
	else if (m_pOwner->m_vPosition.x > m_pOwner->m_StartPos.x + m_PatrolRange)
	{
		m_IsRightEnd = true;
	}

	if (!m_IsRightEnd)
	{
		m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
		m_pOwner->m_IsFront = false;
	}
	else
	{
		m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
		m_pOwner->m_IsFront = true;
	}

	LVector dir = m_pOwner->m_Box.m_Center - player->m_Box.m_Center;

	if (fabs(dir.x) <= m_findTargetRange)
	{
		if (fabs(dir.y) <= m_findTargetRange)
		{
			m_pOwner->SetTransition(Event::FINDTARGET);
			return;
		}
	}
	
	m_pOwner->Move();
}

LMonsterMove::LMonsterMove(LMonster* parent, float actionTimeStart, float actionTimeEnd)
	: MonsterState(parent, actionTimeStart, actionTimeEnd) {}
LMonsterMove::~LMonsterMove() {}