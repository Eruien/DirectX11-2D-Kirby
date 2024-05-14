#include "LBeamFlapping.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LBeamFlapping::Init()
{
	return true;
}

void LBeamFlapping::Process()
{
	LSoundMgr::GetInstance().GetPtr(L"flyup.wav")->Play(false);

	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbytakedamage.wav")->Play(false);
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	if (!m_pOwner->m_isFloor)
	{
		m_pOwner->m_vPosition.y -= m_DownSpeed * g_fSPF;
	}
	
	m_pOwner->m_Speed = m_FlappingSpeed;

	if (LInput::GetInstance().m_dwKeyState[VK_LEFT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = false;
		m_pOwner->m_vPosition.x -= m_pOwner->m_Speed * g_fSPF;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = true;
		m_pOwner->m_vPosition.x += m_pOwner->m_Speed * g_fSPF;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_UP] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_vPosition.y += m_pOwner->m_Speed * g_fSPF;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_UP] == DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}
}

LBeamFlapping::LBeamFlapping(LPlayer* parent, float flappingSpeed, float downSpeed)
: PlayerState(parent), m_FlappingSpeed(flappingSpeed), m_DownSpeed(downSpeed) {}
LBeamFlapping::~LBeamFlapping() {}