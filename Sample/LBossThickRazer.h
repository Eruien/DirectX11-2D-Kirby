#pragma once
#include "LBoss.h"

class LBossThickRazer : public BossState
{
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LBossThickRazer(LBoss* parent);
	virtual ~LBossThickRazer();
};
