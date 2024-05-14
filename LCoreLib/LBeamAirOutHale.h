#pragma once
#include "LPlayer.h"

class LBeamAirOutHale : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LBeamAirOutHale(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 0.15f);
	virtual ~LBeamAirOutHale();
};

