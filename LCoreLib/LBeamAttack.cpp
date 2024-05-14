#include "LBeamAttack.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamAttack::Init()
{
	return true;
}

void LBeamAttack::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	LPlaneObj* monster = m_pOwner->GetCollisionMonster();

	LPlaneObj* boss = m_pOwner->GetCollisionBoss();

	if (monster != nullptr)
	{
		if (m_pOwner->m_pEffect->m_Box.CollisionRect(monster->m_Box))
		{
			monster->m_DeleteFlag = true;
		}
	}

	if (boss != nullptr)
	{
		if (!boss->isInvincibility)
		{
			if (m_pOwner->m_pEffect->m_Box.CollisionRect(boss->m_Box))
			{
				boss->m_IsDamaged = true;
			}
		}
	}

	if (m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0;
		m_pOwner->SetTransition(Event::ENDBEAMATTACK);
		return;
	}
}

LBeamAttack::LBeamAttack(LPlayer* parent, float actionTimeStart, float actionTimeEnd)
	: PlayerState(parent, actionTimeStart, actionTimeEnd) {}
LBeamAttack::~LBeamAttack() {}