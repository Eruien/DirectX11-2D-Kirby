#include "LAngelRunAction.h"
#include "LInput.h"

bool LAngelRunAction::Init()
{
	return true;
}

void LAngelRunAction::Process()
{
	m_pOwner->m_Speed = m_RunSpeed;

	if (!m_pOwner->m_IsFront)
	{
		m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
		if (LInput::GetInstance().m_dwKeyState[VK_LEFT] == DWORD(KeyState::KEY_UP))
		{
			m_pOwner->SetTransition(Event::KEYUP);
			return;
		}
	}

	if (m_pOwner->m_IsFront)
	{
		m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
		if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] == DWORD(KeyState::KEY_UP))
		{
			m_pOwner->SetTransition(Event::KEYUP);
			return;
		}
	}
}

LAngelRunAction::LAngelRunAction(LPlayer* parent, float runSpeed) : PlayerState(parent), m_RunSpeed(runSpeed) {}
LAngelRunAction::~LAngelRunAction() {}
