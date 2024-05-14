#include "LAngelCrouch.h"
#include "LInput.h"

bool LAngelCrouch::Init()
{
	return true;
}

void LAngelCrouch::Process()
{
	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = false;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = true;
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] == DWORD(KeyState::KEY_PUSH))
	{
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_DOWN] == DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}
}

LAngelCrouch::LAngelCrouch(LPlayer* parent) : PlayerState(parent) {}
LAngelCrouch::~LAngelCrouch() {}