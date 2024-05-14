#include "LTakeDamage.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LTakeDamage::Init()
{
	return true;
}

void LTakeDamage::Process()
{
	if (m_pOwner->m_IsFront)
	{
		m_pOwner->m_vPosition.x -= 300.0f * g_fSPF;
	}
	else
	{
		m_pOwner->m_vPosition.x += 300.0f * g_fSPF;
	}

	m_pOwner->m_vPosition.y -= 300.0f * g_fSPF;
	m_pOwner->m_InvincibilityTime = true;
	m_pOwner->isInvincibility = true;
	m_pOwner->isDamaged = false;

	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->m_Life -= 1;
		m_pOwner->m_LifeCounter->m_AnimationIndex += 1;

		/*if (m_pOwner->m_Life == 0)
		{
			m_pOwner->SetTransition(Event::HURT);
			return;
		}*/

		m_pOwner->SetTransition(Event::ENDROLLING);
	}
}

LTakeDamage::LTakeDamage(LPlayer* parent, float walkSpeed) : PlayerState(parent), m_WalkSpeed(walkSpeed) {}
LTakeDamage::~LTakeDamage() {}
