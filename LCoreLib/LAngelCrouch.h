#pragma once
#include "LPlayer.h"

class LAngelCrouch : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LAngelCrouch(LPlayer* parent);
	virtual ~LAngelCrouch();
};

