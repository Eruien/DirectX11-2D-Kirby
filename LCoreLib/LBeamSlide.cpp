#include "LBeamSlide.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamSlide::Init()
{
	return true;
}

void LBeamSlide::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	m_pOwner->m_Speed = m_SlideSpeed;
	m_ActionTimeStart += g_fSPF;

	if (m_ActionTimeEnd <= m_ActionTimeStart)
	{
		m_ActionTimeStart = 0.0f;
		m_pOwner->SetTransition(Event::ENDSLIDETIME);
		return;
	}

	if (m_pOwner->m_IsFront)
	{
		m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
		return;
	}
	else
	{
		m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
		return;
	}
}

LBeamSlide::LBeamSlide(LPlayer* parent, float slideSpeed, float actionTimeStart, float actionTimeEnd)
: PlayerState(parent, actionTimeStart, actionTimeEnd), m_SlideSpeed(slideSpeed) {}
LBeamSlide::~LBeamSlide() {}