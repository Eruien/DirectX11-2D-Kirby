#include "LPlayer.h"

class LFatMode : public PlayerState
{
public:
	float m_FatSpeed = 150.0f;
public:
	float m_RunTimeReset;
public:
	bool Init() override;
	void Process() override;
public:
	LFatMode(LPlayer* parent, float runTimeReset = 0.08f);
	virtual ~LFatMode();
};

