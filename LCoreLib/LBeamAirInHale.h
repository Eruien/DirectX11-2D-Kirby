#pragma once
#include "LPlayer.h"

class LBeamAirInHale : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LBeamAirInHale(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LBeamAirInHale();
};

