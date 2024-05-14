#pragma once
#include "LPlayer.h"

class LSecondInHale : public PlayerState
{
public:
	float m_DragSpeed = 300.0f;
public:
	bool Init() override;
	void Process() override;
public:
	LSecondInHale(LPlayer* parent, float actionTimeStart = 0.0f, float actionTimeEnd = 2.5f);
	virtual ~LSecondInHale();
};


