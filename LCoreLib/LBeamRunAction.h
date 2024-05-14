#pragma once
#include "LPlayer.h"

class LBeamRunAction : public PlayerState
{
public:
	float m_RunSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LBeamRunAction(LPlayer* parent, float runSpeed = 400.0f);
	virtual ~LBeamRunAction();
};



