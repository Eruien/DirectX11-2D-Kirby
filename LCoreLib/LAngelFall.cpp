#include "LAngelFall.h"
#include "LInput.h"

bool LAngelFall::Init()
{
	return true;
}

void LAngelFall::Process()
{
	m_pOwner->m_vPosition.y -= m_pOwner->m_Speed * g_fSPF;

	if (m_pOwner->m_isFloor)
	{
		m_pOwner->SetTransition(Event::COLLISIONFLOOR);
		return;
	}
}

LAngelFall::LAngelFall(LPlayer* parent) : PlayerState(parent) {}
LAngelFall::~LAngelFall() {}