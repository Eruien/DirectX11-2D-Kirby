#pragma once
#include "LPlayer.h"

class LBeamFall : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LBeamFall(LPlayer* parent);
	virtual ~LBeamFall();
};

