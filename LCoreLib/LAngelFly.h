#pragma once
#include "LPlayer.h"

class LAngelFly : public PlayerState
{
public:
	float m_FlySpeed;
	float m_DownSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LAngelFly(LPlayer* parent, float flySpeed = 300.0f, float downSpeed = 100.0f);
	virtual ~LAngelFly();
};
