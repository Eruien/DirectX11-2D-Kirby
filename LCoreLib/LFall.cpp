#include "LFall.h"
#include "LInput.h"

bool LFall::Init()
{
	return true;
}

void LFall::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;

	if (m_pOwner->m_isFloor)
	{
		m_pOwner->SetTransition(Event::COLLISIONFLOOR);
		return;
	}
}

LFall::LFall(LPlayer* parent) : PlayerState(parent) {}
LFall::~LFall() {}