#include "LSecondInHale.h"
#include "LInput.h"
#include "LSoundMgr.h"

bool LSecondInHale::Init()
{
	return true;
}

void LSecondInHale::Process()
{
	LSoundMgr::GetInstance().GetPtr(L"kirbyinhale.wav")->Play(false);

	if (!m_pOwner->isInvincibility && m_pOwner->isDamaged)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbyinhale.wav")->Stop();
		m_pOwner->SetTransition(Event::HURT);
		return;
	}

	LPlaneObj* monster = m_pOwner->GetCollisionMonster();

	if (monster != nullptr)
	{
		if (m_pOwner->m_pEffect->m_Box.CollisionRect(monster->m_Box))
		{
			LVector dir = m_pOwner->m_Box.m_Center - monster->m_Box.m_Center;

			monster->m_vPosition.x += dir.NormalVector().x * m_DragSpeed * g_fSPF;

			if (fabs(dir.x) <= 20)
			{
				if (fabs(dir.y) <= 20)
				{
					LSoundMgr::GetInstance().GetPtr(L"kirbyinhale.wav")->Stop();
					monster->m_DeleteFlag = true;
					m_pOwner->SetTransition(Event::ABSORBMONSTER);
					return;
				}
			}
		}
	}

	if (LInput::GetInstance().m_dwKeyState['Z'] == DWORD(KeyState::KEY_UP))
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbyinhale.wav")->Stop();
		m_pOwner->SetTransition(Event::KEYUP);
		return;
	}

	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		LSoundMgr::GetInstance().GetPtr(L"kirbyinhale.wav")->Stop();
		m_pOwner->SetTransition(Event::ENDINHALE);
		return;
	}
}

LSecondInHale::LSecondInHale(LPlayer* parent, float actionTimeStart, float actionTimeEnd)
	: PlayerState(parent, actionTimeStart, actionTimeEnd) {}
LSecondInHale::~LSecondInHale() {}