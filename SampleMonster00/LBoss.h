#pragma once
#include "LAnimation.h"
#include "LFSMMgr.h"
#include "LSpriteUVObj.h"
#include "LLife.h"

class LBoss;

class BossState
{
protected:
	LBoss* m_pOwner = nullptr;
	float m_findTargetRange = 100.0f;
	float m_PatrolRange = 300.0f;
public:
	float m_ActionTimeStart = 0.0f;
	float m_ActionTimeEnd = 0.0f;
public:
	virtual bool Init() { return true; }
	virtual	void Process(LPlaneObj* player) = 0;
public:
	BossState(LBoss* parent) : m_pOwner(parent) {}
	virtual ~BossState() {}
};

class LBoss : public LPlaneObj
{
public:
	std::vector<LSpriteUVObj*> m_StarList;
	std::vector<LSpriteUVObj*> m_RazerList;
	std::unique_ptr<LSpriteUVObj> m_DamagedEffect = nullptr;
	std::unique_ptr<LLife> m_LifeCounter = nullptr;
	int m_Life = 6;
	bool isDead = false;

	float m_InvincibilityStart = 0.0f;
	float m_InvincibilityEnd = 1.0f;
	bool m_InvincibilityTime = false;
public:
	void CreateRazer();
	void CreateThickRazer();
	void ClearRazer();
	void CreateThreeStar();
	void ClearThreeStar();
public:
	float m_HalfMapsizeX = 0.0f;
	float m_HalfMapsizeY = 0.0f;
	LVector m_StartPos = { 0.0f, 0.0f, 1.0f };
	float m_Speed = 200.0f;
	bool m_LeftEnd = false;
	bool m_RightEnd = true;
	bool m_IsFront = false;
	bool m_isFloor = false;
	LBox m_FloorBox;
public:
	State m_CurrentState = State::NONE;
	LFiniteStateMachine* m_pFsm = nullptr;
	BossState* m_pAction = nullptr;
	std::map<State, std::unique_ptr<BossState>> m_pActionList;
	std::map<State, std::unique_ptr<LAnimation>> m_AnimationList;
	std::map<State, std::wstring> m_TextList;
public:
	void FSM(FSMType fsmType);
	void SetTransition(Event inputEvent);
	State GetState();
public:
	void Move();
public:
	virtual	void Process(LPlaneObj* player);
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	LBoss();
	virtual ~LBoss();
};

