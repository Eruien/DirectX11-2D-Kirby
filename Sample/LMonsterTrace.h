#pragma once
#include "LMonster.h"

class LMonsterTrace : public MonsterState
{
public:
	float m_AttackRange = 50.0f;
	float m_TraceRange = 150.0f;
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LMonsterTrace(LMonster* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LMonsterTrace();
};


