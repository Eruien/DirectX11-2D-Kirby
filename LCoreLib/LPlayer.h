#pragma once
#include "LSpriteUVObj.h"
#include "LAnimation.h"
#include "LFSMMgr.h"
#include "LLife.h"

class LPlayer;
class LEffect;

class PlayerState
{
protected:
	LPlayer* m_pOwner = nullptr;
public:
	float m_ActionTimeStart = 0.0f;
	float m_ActionTimeEnd = 0.0f;
public:
	virtual bool Init() { return true; }
	virtual	void Process() = 0;
public:
	PlayerState(LPlayer* parent) : m_pOwner(parent) {}
	PlayerState(LPlayer* parent, float ActionTimeStart, float ActionTimeEnd)
		: m_pOwner(parent), m_ActionTimeStart(ActionTimeStart), m_ActionTimeEnd(ActionTimeEnd) {}
	virtual ~PlayerState() {}
};

class PlayerBeamState : public PlayerState
{
public:
	PlayerBeamState(LPlayer* parent)
	: PlayerState(parent) {}  
	PlayerBeamState(LPlayer* parent, float ActionTimeStart, float ActionTimeEnd)
	: PlayerState(parent, ActionTimeStart, ActionTimeEnd) {} 
	virtual ~PlayerBeamState() {}
};


class LPlayer : public LPlaneObj
{
public:
	float m_RunTimeLeft = 0.0f;
	bool m_StartTimeLeft = false;
	bool m_IsRunLeft = false;

	float m_RunTimeRight = 0.0f;
	bool m_StartTimeRight = false;
	bool m_IsRunRight = false;
public:
	bool m_IsFront = true;
	bool m_isFloor = false;
	float m_Speed = 200.0f;

	float m_HalfMapX = 0.0f;
	float m_HalfMapY = 0.0f;
public:
	State m_CurrentState = State::NONE;
	LFiniteStateMachine* m_pFsm = nullptr;
	PlayerState* m_pAction = nullptr;
	PlayerState* m_pCheckAction = nullptr;
	std::map<State, std::unique_ptr<PlayerState>> m_pActionList;
	std::map<State, std::unique_ptr<LAnimation>> m_AnimationList;
	std::map<State, std::wstring> m_TextList;
	LBox m_FloorBox;
	std::vector<LSpriteUVObj*> m_StarList;
	std::vector<LSpriteUVObj*> m_RazerList;
	std::unique_ptr<LEffect> m_pEffect;
	std::unique_ptr<LEffect> m_pBeamEffect;
	LPlaneObj* m_pMonster;
	LPlaneObj* m_pBoss;
	std::unique_ptr<LLife> m_LifeCounter = nullptr;
	int m_Life = 6;
	bool isInvincibility = false;
	bool isDamaged = false;
	bool isDead = false;

	float m_InvincibilityStart = 0.0f;
	float m_InvincibilityEnd = 2.0f;
	bool m_InvincibilityTime = false;
public:
	bool CreateVertexBuffer() override;
public:
	void FSM(FSMType fsmType);
	void SetTransition(Event inputEvent);
	State GetState();
	void SetCollisionMonster(LPlaneObj* pMonster);
	LPlaneObj* GetCollisionMonster();
	void SetCollisionBoss(LPlaneObj* pBoss);
	LPlaneObj* GetCollisionBoss();
public:
	virtual	void Process();
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	LPlayer();
	virtual ~LPlayer();
};

class LEffect : public LPlayer
{
public:
	LPlayer* m_pPlayer;
	State m_CurrentState = State::NONE;
	std::map<State, std::unique_ptr<LAnimation>> m_AnimationList;
	float m_EffectDistance = 0.0f;
public:
	void SetEffect(LPlayer* pPlayer, std::wstring shaderfilePath, std::wstring texfilePath, float widthScale, float heightScale);
public:
	bool Init() override;
	bool Frame();
	bool Render();
};

