#pragma once
#include "LPlayer.h"

class LModeChange : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LModeChange(LPlayer* parent);
	virtual ~LModeChange();
};

