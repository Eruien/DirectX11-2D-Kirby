#include "LAngelAttack.h"
#include "LInput.h"

bool LAngelAttack::Init()
{
	return true;
}

void LAngelAttack::Process()
{

	LPlaneObj* monster = m_pOwner->GetCollisionMonster();

	if (monster == nullptr) return;

	if (m_pOwner->m_pEffect->m_Box.CollisionRect(monster->m_Box))
	{	
		monster->m_DeleteFlag = true;
		return;
	}

	if (m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->m_pEffect->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0;
		m_pOwner->SetTransition(Event::ENDBEAMATTACK);
		return;
	}
}

LAngelAttack::LAngelAttack(LPlayer* parent, float actionTimeStart, float actionTimeEnd)
	: PlayerState(parent, actionTimeStart, actionTimeEnd) {}
LAngelAttack::~LAngelAttack() {}