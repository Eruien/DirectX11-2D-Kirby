#include "LBeamIdleAction.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamIdleAction::Init()
{
	return true;
}

void LBeamIdleAction::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = false;
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
			LSoundMgr::GetInstance().GetPtr(L"runStart.wav")->Play(false);
			m_pOwner->SetTransition(Event::RUNTIME);
			return;
		}
		m_pOwner->SetTransition(Event::INPUTLR);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = true;
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
			LSoundMgr::GetInstance().GetPtr(L"runStart.wav")->Play(false);
			m_pOwner->SetTransition(Event::RUNTIME);
			return;
		}

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
		LSoundMgr::GetInstance().GetPtr(L"cancleability.wav")->Play(false);
		m_pOwner->SetTransition(Event::INPUTCANCLE);
		return;
	}
}

LBeamIdleAction::LBeamIdleAction(LPlayer* parent, float runTimeReset) : PlayerState(parent), m_RunTimeReset(runTimeReset) {}
LBeamIdleAction::~LBeamIdleAction() {}