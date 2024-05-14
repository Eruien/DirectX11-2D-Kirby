#pragma once
#include "LBoss.h"

class LBossIdle : public BossState
{
public:
	bool m_UseStar = false;
	float m_UseStarTime = 0.0f;
	float m_StarCoolTime = 2.0f;

	bool m_UseRazer = false;
	float m_UseRazerTime = 0.0f;
	float m_RazerCoolTime = 10.0f;
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LBossIdle(LBoss* parent);
	virtual ~LBossIdle();
};


