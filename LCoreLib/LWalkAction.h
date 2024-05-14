#pragma once
#include "LPlayer.h"

class LWalkAction : public PlayerState
{
public:
	float m_WalkSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LWalkAction(LPlayer* parent, float walkSpeed = 200.0f);
	virtual ~LWalkAction();
};

