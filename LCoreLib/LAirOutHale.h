#pragma once
#include "LPlayer.h"

class LAirOutHale : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LAirOutHale(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LAirOutHale();
};

