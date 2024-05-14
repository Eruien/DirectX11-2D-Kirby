#include "LPlayer.h"

class LDeadAction : public PlayerState
{
public:
	float m_DelayStart = 0.0f;
	float m_DelayEnd = 0.2f;
public:
	bool Init() override;
	void Process() override;
public:
	LDeadAction(LPlayer* parent, float runTimeReset = 0.08f);
	virtual ~LDeadAction();
};

