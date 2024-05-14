#pragma once
#include "LPlayer.h"

class LIdleAction : public PlayerState
{
public:
	float m_RunTimeReset;
public:
	bool Init() override;
	void Process() override;	
public:
	LIdleAction(LPlayer* parent, float runTimeReset = 0.3f);
	virtual ~LIdleAction();
};

