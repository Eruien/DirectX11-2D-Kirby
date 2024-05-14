#include "LModeChange.h"
#include "LInput.h"

bool LModeChange::Init()
{
	return true;
}

void LModeChange::Process()
{
	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		m_pOwner->SetTransition(Event::CHANGEABILITY);
		return;
	}
}

LModeChange::LModeChange(LPlayer* parent) : PlayerState(parent) {}
LModeChange::~LModeChange() {}