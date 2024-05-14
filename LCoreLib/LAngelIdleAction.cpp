#include "LAngelIdleAction.h"
#include "LInput.h"

bool LAngelIdleAction::Init()
{
	return true;
}

void LAngelIdleAction::Process()
{
	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
	{
		if (m_pOwner->m_RunTimeLeft > m_RunTimeReset)
		{
			m_pOwner->m_RunTimeLeft = 0.0f;
			m_pOwner->m_StartTimeLeft = false;
			m_pOwner->m_IsRunLeft = false;
		}

		if (m_pOwner->m_IsRunLeft)
		{
			m_pOwner->m_RunTimeLeft = 0.0f;
			m_pOwner->m_StartTimeLeft = false;
			m_pOwner->m_IsRunLeft = false;
			m_pOwner->SetTransition(Event::RUNTIME);
			return;
		}

		m_pOwner->m_IsFront = false;
		m_pOwner->SetTransition(Event::INPUTLR);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		if (m_pOwner->m_RunTimeRight > m_RunTimeReset)
		{
			m_pOwner->m_RunTimeRight = 0.0f;
			m_pOwner->m_StartTimeRight = false;
			m_pOwner->m_IsRunRight = false;
		}

		if (m_pOwner->m_IsRunRight)
		{
			m_pOwner->m_RunTimeRight = 0.0f;
			m_pOwner->m_StartTimeRight = false;
			m_pOwner->m_IsRunRight = false;
			m_pOwner->SetTransition(Event::RUNTIME);
			return;
		}

		m_pOwner->m_IsFront = true;
		m_pOwner->SetTransition(Event::INPUTLR);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_UP] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTUP);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_DOWN] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTDOWN);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState['X'] > DWORD(KeyState::KEY_UP))
	{

		m_pOwner->SetTransition(Event::INPUTCANCLE);
		return;
	}
}

LAngelIdleAction::LAngelIdleAction(LPlayer* parent, float runTimeReset) : PlayerState(parent), m_RunTimeReset(runTimeReset) {}
LAngelIdleAction::~LAngelIdleAction() {}