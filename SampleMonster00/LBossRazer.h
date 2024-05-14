#pragma once
#include "LBoss.h"

class LBossRazer : public BossState
{
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LBossRazer(LBoss* parent);
	virtual ~LBossRazer();
};
