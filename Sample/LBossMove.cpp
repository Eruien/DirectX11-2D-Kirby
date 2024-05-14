#include "LBossMove.h"
#include <random>
#include <chrono>

bool LBossMove::Init()
{
	return true;
}

void LBossMove::Process(LPlaneObj* player)
{
	std::vector<LVector> bossPos;
	bossPos.push_back({ m_pOwner->m_HalfMapsizeX - m_pOwner->m_vScale.x,
	-m_pOwner->m_HalfMapsizeY + m_pOwner->m_vScale.y + 64.0f, 1.0f });
	bossPos.push_back({ -m_pOwner->m_HalfMapsizeX + m_pOwner->m_vScale.x,
	-m_pOwner->m_HalfMapsizeY + m_pOwner->m_vScale.y + 64.0f, 1.0f });

	bossPos.push_back({ m_pOwner->m_HalfMapsizeX - m_pOwner->m_vScale.x,
	-m_pOwner->m_HalfMapsizeY + m_pOwner->m_vScale.y + 192.0f, 1.0f });
	bossPos.push_back({ -m_pOwner->m_HalfMapsizeX + m_pOwner->m_vScale.x,
	-m_pOwner->m_HalfMapsizeY + m_pOwner->m_vScale.y + 192.0f, 1.0f });

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// default_random_engine 객체를 만들고, 위에서 만든 seed 값을 사용합니다.
	std::default_random_engine generator(seed);

	// 0부터 3까지의 균일 분포를 만듭니다.
	std::uniform_int_distribution<int> distribution(0, 3);

	// 랜덤한 숫자를 생성하고 출력합니다.
	
	if (m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex ==
		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_UVList.size() - 1)
	{
		

		int random_number = distribution(generator);
		m_pOwner->m_vPosition.x = bossPos[random_number].x;
		m_pOwner->m_vPosition.y = bossPos[random_number].y;

		if (m_pOwner->m_vPosition.x < 0)
		{
			m_pOwner->m_IsFront = true;
		}
		else
		{
			m_pOwner->m_IsFront = false;
		}

		m_pOwner->m_AnimationList[m_pOwner->m_CurrentState]->m_AnimationIndex = 0.0f;
		m_pOwner->SetTransition(Event::BOSSSTARATTACK);
		return;
	}

}

LBossMove::LBossMove(LBoss* parent) : BossState(parent) {}
LBossMove::~LBossMove() {}