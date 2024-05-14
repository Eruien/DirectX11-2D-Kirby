#include "LBeamRunAction.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamRunAction::Init()
{
	return true;
}

void LBeamRunAction::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

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

LBeamRunAction::LBeamRunAction(LPlayer* parent, float runSpeed) : PlayerState(parent), m_RunSpeed(runSpeed) {}
LBeamRunAction::~LBeamRunAction() {}
