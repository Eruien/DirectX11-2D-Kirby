#include "LFatIdle.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LFatIdle::Init()
{
	return true;
}

void LFatIdle::Process()
{
	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	m_DelayStart += g_fSPF;

	if (m_DelayStart < m_DelayEnd)
	{
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = false;
		m_pOwner->SetTransition(Event::INPUTLR);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = true;
		m_pOwner->SetTransition(Event::INPUTLR);
		return;
	}

	/*if (LInput::GetInstance().m_dwKeyState['1'] > DWORD(KeyState::KEY_UP))
	{
		m_DelayStart = 0.0f;
		m_pOwner->SetTransition(Event::CHANGEANGEL);
		return;
	}*/

	if (LInput::GetInstance().m_dwKeyState[VK_DOWN] > DWORD(KeyState::KEY_UP))
	{
		m_DelayStart = 0.0f;
		LSoundMgr::GetInstance().GetPtr(L"abilityGet.wav")->Play(false);
		m_pOwner->SetTransition(Event::INPUTDOWN);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] == DWORD(KeyState::KEY_PUSH))
	{
		LSoundMgr::GetInstance().GetPtr(L"cancleability.wav")->Play(false);
		m_DelayStart = 0.0f;
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}
}

LFatIdle::LFatIdle(LPlayer* parent, float runTimeReset) : PlayerState(parent) {}
LFatIdle::~LFatIdle() {}