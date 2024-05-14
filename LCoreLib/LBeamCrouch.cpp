#include "LBeamCrouch.h"
#include "LInput.h"
#include "LSoundMgr.h"
#include "LSoundMgr.h"


bool LBeamCrouch::Init()
{
	return true;
}

void LBeamCrouch::Process()
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
	}

	if (LInput::GetInstance().m_dwKeyState[VK_RIGHT] > DWORD(KeyState::KEY_UP))
	{
		m_pOwner->m_IsFront = true;
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] == DWORD(KeyState::KEY_PUSH))
	{
		LSoundMgr::GetInstance().GetPtr(L"slide.wav")->Play(false);
		m_pOwner->SetTransition(Event::INPUTATTACK);
		return;
	}

	if (LInput::GetInstance().m_dwKeyState[VK_DOWN] == DWORD(KeyState::KEY_UP))
	{
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}
}

LBeamCrouch::LBeamCrouch(LPlayer* parent) : PlayerState(parent) {}
LBeamCrouch::~LBeamCrouch() {}