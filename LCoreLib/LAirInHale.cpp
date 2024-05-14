#include "LAirInHale.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LAirInHale::Init()
{
	return true;
}

void LAirInHale::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	m_ActionTimeStart += g_fSPF;

	if (m_ActionTimeEnd <= m_ActionTimeStart)
	{
		m_ActionTimeStart = 0.0f;
		m_pOwner->SetTransition(Event::CHANGEFLY);
		return;
	}
}

LAirInHale::LAirInHale(LPlayer* parent, float actionTimeStart, float actionTimeEnd)
: PlayerState(parent, actionTimeStart, actionTimeEnd) {}
LAirInHale::~LAirInHale() {}