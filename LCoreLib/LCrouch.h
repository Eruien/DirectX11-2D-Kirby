#pragma once
#include "LPlayer.h"

class LCrouch : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LCrouch(LPlayer* parent);
	virtual ~LCrouch();
};

