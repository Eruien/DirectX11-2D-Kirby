#include "LMonsterAttack.h"

bool LMonsterAttack::Init()
{
	return true;
}

void LMonsterAttack::Process(LPlaneObj* player)
{
	m_ActionTimeStart += g_fSPF;

	if (m_ActionTimeEnd >= m_ActionTimeStart)
	{
		return;
	}

	LVector dir = m_pOwner->m_Box.m_Center - player->m_Box.m_Center;

	if (fabs(dir.x) <= m_AttackRange)
	{
		if (fabs(dir.y) <= m_AttackRange)
		{
			m_ActionTimeStart = 0.0f;
			return;
		}
	}

	m_pOwner->SetTransition(Event::OUTATTACKRANGE);
}

LMonsterAttack::LMonsterAttack(LMonster* parent, float actionTimeStart, float actionTimeEnd)
	: MonsterState(parent, actionTimeStart, actionTimeEnd) {}
LMonsterAttack::~LMonsterAttack() {}