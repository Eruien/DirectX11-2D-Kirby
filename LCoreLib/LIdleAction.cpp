#include "LIdleAction.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LIdleAction::Init()
{
	return true;
}

void LIdleAction::Process()
{
	m_pOwner->m_vPosition.y -= 300.0f * g_fSPF;

	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

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
			LSoundMgr::GetInstance().GetPtr(L"runStart.wav")->Play(false);
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
			LSoundMgr::GetInstance().GetPtr(L"runStart.wav")->Play(false);
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
}

LIdleAction::LIdleAction(LPlayer* parent, float runTimeReset) : PlayerState(parent), m_RunTimeReset(runTimeReset) {}
LIdleAction::~LIdleAction() {}