#include "LAngelFly.h"
#include "LInput.h"

bool LAngelFly::Init()
{
	return true;
}

void LAngelFly::Process()
{
	if (!m_pOwner->m_isFloor)
	{
		m_pOwner->m_vPosition.y -= m_DownSpeed * g_fSPF;
	}

	m_pOwner->m_Speed = m_FlySpeed;

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

	if (LInput::GetInstance().m_dwKeyState['Z'] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_UP] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::INPUTUP);
		return;
	}
}

LAngelFly::LAngelFly(LPlayer* parent, float flySpeed, float downSpeed)
: PlayerState(parent), m_FlySpeed(flySpeed), m_DownSpeed(downSpeed) {}
LAngelFly::~LAngelFly() {}