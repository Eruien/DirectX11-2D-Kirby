#pragma once
#include "LPlayer.h"

class LFall : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LFall(LPlayer* parent);
	virtual ~LFall();
};

