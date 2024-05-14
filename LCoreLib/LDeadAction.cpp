#include "LDeadAction.h"
#include "LInput.h"

bool LDeadAction::Init()
{
	return true;
}

void LDeadAction::Process()
{
	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->isDead = true;
		return;
	}
}

LDeadAction::LDeadAction(LPlayer* parent, float runTimeReset) : PlayerState(parent) {}
LDeadAction::~LDeadAction() {}