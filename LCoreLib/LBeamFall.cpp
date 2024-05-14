#include "LBeamFall.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamFall::Init()
{
	return true;
}

void LBeamFall::Process()
{
	m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;

	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	if (m_pOwner->m_isFloor)
	{
		m_pOwner->SetTransition(Event::COLLISIONFLOOR);
		return;
	}
}

LBeamFall::LBeamFall(LPlayer* parent) : PlayerState(parent) {}
LBeamFall::~LBeamFall() {}