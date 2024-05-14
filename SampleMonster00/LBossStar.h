#pragma once
#include "LBoss.h"

class LBossStar : public BossState
{
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LBossStar(LBoss* parent);
	virtual ~LBossStar();
};
