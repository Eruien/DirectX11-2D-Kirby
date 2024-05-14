#pragma once
#include "LPlayer.h"

class LFlapping : public PlayerState
{
public:
	float m_FlappingSpeed;
	float m_DownSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LFlapping(LPlayer* parent, float flappingSpeed = 300.0f, float downSpeed = 100.0f);
	virtual ~LFlapping();
};

