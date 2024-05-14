#pragma once
#include "LPlayer.h"

class LBeamCrouch : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LBeamCrouch(LPlayer* parent);
	virtual ~LBeamCrouch();
};

