#pragma once
#include "LPlayer.h"

class LAngelWalkAction : public PlayerState
{
public:
	float m_WalkSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LAngelWalkAction(LPlayer* parent, float walkSpeed = 200.0f);
	virtual ~LAngelWalkAction();
};

