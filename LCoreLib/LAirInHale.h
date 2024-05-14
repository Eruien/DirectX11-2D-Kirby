#pragma once
#include "LPlayer.h"

class LAirInHale : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LAirInHale(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LAirInHale();
};

