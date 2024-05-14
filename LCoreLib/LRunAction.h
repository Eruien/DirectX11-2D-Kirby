#pragma once
#include "LPlayer.h"

class LRunAction : public PlayerState
{
public:
	float m_RunSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LRunAction(LPlayer* parent, float runSpeed = 400.0f);
	virtual ~LRunAction();
};



