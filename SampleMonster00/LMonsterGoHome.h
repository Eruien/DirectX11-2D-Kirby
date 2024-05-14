#pragma once
#include "LMonster.h"

class LMonsterGoHome : public MonsterState
{
public:
	bool m_HomeRange = 5.0f;
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LMonsterGoHome(LMonster* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LMonsterGoHome();
};


