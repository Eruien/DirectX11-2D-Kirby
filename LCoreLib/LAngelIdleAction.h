#pragma once
#include "LPlayer.h"

class LAngelIdleAction : public PlayerState
{
public:
	float m_RunTimeReset;
public:
	bool Init() override;
	void Process() override;	
public:
	LAngelIdleAction(LPlayer* parent, float runTimeReset = 0.08f);
	virtual ~LAngelIdleAction();
};

