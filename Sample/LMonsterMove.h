#pragma once
#include "LMonster.h"

class LMonsterMove : public MonsterState
{
public:
	bool m_IsRightEnd = false;
public:
	bool Init() override;
	void Process(LPlaneObj* player) override;
public:
	LMonsterMove(LMonster* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LMonsterMove();
};


