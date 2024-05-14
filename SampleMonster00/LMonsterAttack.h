#pragma once
#include "LMonster.h"

class LMonsterAttack : public MonsterState
{
public:
	float m_AttackRange = 50.0f;
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LMonsterAttack(LMonster* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 2.0f);
	virtual ~LMonsterAttack();
};


