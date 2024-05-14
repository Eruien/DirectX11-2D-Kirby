#pragma once
#include "LPlayer.h"

class LBeamSlide : public PlayerState
{
public:
	float m_SlideSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LBeamSlide(LPlayer* parent, float slideSpeed = 300.0f, float actionTimeStart = 0.0f, float actionTimeEnd = 0.5f);
	virtual ~LBeamSlide();
};

