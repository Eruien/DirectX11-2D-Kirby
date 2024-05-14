#include "LBeamAirInHale.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamAirInHale::Init()
{
	return true;
}

void LBeamAirInHale::Process()
{
	m_ActionTimeStart += g_fSPF;

	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	if (m_ActionTimeEnd <= m_ActionTimeStart)
	{
		m_ActionTimeStart = 0.0f;
		m_pOwner->SetTransition(Event::CHANGEFLY);
		return;
	}
}

LBeamAirInHale::LBeamAirInHale(LPlayer* parent, float actionTimeStart, float actionTimeEnd)
: PlayerState(parent, actionTimeStart, actionTimeEnd) {}
LBeamAirInHale::~LBeamAirInHale() {}