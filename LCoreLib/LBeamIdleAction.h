#pragma once
#include "LPlayer.h"

class LBeamIdleAction : public PlayerState
{
public:
	float m_RunTimeReset;
public:
	bool Init() override;
	void Process() override;	
public:
	LBeamIdleAction(LPlayer* parent, float runTimeReset = 0.08f);
	virtual ~LBeamIdleAction();
};

