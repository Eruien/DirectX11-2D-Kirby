#include "LAngelSlide.h"
#include "LInput.h"

bool LAngelSlide::Init()
{
	return true;
}

void LAngelSlide::Process()
{
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

LAngelSlide::LAngelSlide(LPlayer* parent, float slideSpeed, float actionTimeStart, float actionTimeEnd)
: PlayerState(parent, actionTimeStart, actionTimeEnd), m_SlideSpeed(slideSpeed) {}
LAngelSlide::~LAngelSlide() {}