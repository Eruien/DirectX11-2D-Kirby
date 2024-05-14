#pragma once
#include "LPlayer.h"

class LBeamAttack : public PlayerState
{
public:
	float m_DragSpeed = 200.0f;
public:
	bool Init() override;
	void Process() override;
public:
	LBeamAttack(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 2.5f);
	virtual ~LBeamAttack();
};


