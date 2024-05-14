#include "LPlayer.h"

class LTakeDamage : public PlayerState
{
public:
	float m_WalkSpeed;
public:
	bool Init() override;
	void Process() override;
public:
	LTakeDamage(LPlayer* parent, float walkSpeed = 200.0f);
	virtual ~LTakeDamage();
};

