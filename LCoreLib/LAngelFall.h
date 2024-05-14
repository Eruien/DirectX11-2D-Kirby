#pragma once
#include "LPlayer.h"

class LAngelFall : public PlayerState
{
public:
	bool Init() override;
	void Process() override;
public:
	LAngelFall(LPlayer* parent);
	virtual ~LAngelFall();
};

