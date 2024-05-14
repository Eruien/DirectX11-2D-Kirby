#pragma once
#include "LBoss.h"

class LBossRazerReady : public BossState
{
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LBossRazerReady(LBoss* parent);
	virtual ~LBossRazerReady();
};
