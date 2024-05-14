#include "LFatMode.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LFatMode::Init()
{
	return true;
}

void LFatMode::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	m_pOwner->m_Speed = m_FatSpeed;

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

LFatMode::LFatMode(LPlayer* parent, float runTimeReset) : PlayerState(parent), m_RunTimeReset(runTimeReset) {}
LFatMode::~LFatMode() {}