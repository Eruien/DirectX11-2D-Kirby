#pragma once
#include "LPlayer.h"

class LBeamWalkAction : public PlayerState
{
public:
	float m_WalkSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LBeamWalkAction(LPlayer* parent, float walkSpeed = 200.0f);
	virtual ~LBeamWalkAction();
};

