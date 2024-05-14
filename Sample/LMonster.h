#pragma once
#include "LPlaneObj.h"
#include "LAnimation.h"
#include "LFSMMgr.h"

class LMonster;

class MonsterState
{
protected:
	LMonster* m_pOwner = nullptr;
	float m_findTargetRange = 100.0f;
	float m_PatrolRange = 300.0f;
public:
	float m_ActionTimeStart = 0.0f;
	float m_ActionTimeEnd = 0.0f;
public:
	virtual bool Init() { return true; }
	virtual	void Process(LPlaneObj* player) = 0;
public:
	MonsterState(LMonster* parent) : m_pOwner(parent) {}
	MonsterState(LMonster* parent, float ActionTimeStart, float ActionTimeEnd)
		: m_pOwner(parent), m_ActionTimeStart(ActionTimeStart), m_ActionTimeEnd(ActionTimeEnd) {}
	virtual ~MonsterState() {}
};

class MonsterBeamState : public MonsterState
{

};

class LMonster : public LPlaneObj
{
public:
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
	MonsterState* m_pAction = nullptr;
	std::map<State, std::unique_ptr<MonsterState>> m_pActionList;
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
	LMonster();
	virtual ~LMonster();
};

