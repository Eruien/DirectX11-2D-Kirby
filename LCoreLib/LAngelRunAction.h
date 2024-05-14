#pragma once
#include "LPlayer.h"

class LAngelRunAction : public PlayerState
{
public:
	float m_RunSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LAngelRunAction(LPlayer* parent, float runSpeed = 400.0f);
	virtual ~LAngelRunAction();
};



