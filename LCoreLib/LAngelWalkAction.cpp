#include "LAngelWalkAction.h"
#include "LInput.h"

bool LAngelWalkAction::Init()
{
	return true;
}

void LAngelWalkAction::Process()
{
	m_pOwner->m_Speed = m_WalkSpeed;

	if (!m_pOwner->m_IsFront)
	{
		if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
		{
			m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
			return;
		}
	}
	
	if (m_pOwner->m_IsFront)
	{
		if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
		{
			m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
			return;
		}
	}
	
	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] == DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_StartTimeLeft = true;
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] == DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_StartTimeRight = true;
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}
}

LAngelWalkAction::LAngelWalkAction(LPlayer* parent, float walkSpeed) : PlayerState(parent), m_WalkSpeed(walkSpeed) {}
LAngelWalkAction::~LAngelWalkAction() {}
