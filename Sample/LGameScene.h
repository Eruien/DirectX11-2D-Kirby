#pragma once
#include "LScene.h"
#include "LPlayer.h"
#include "LMonster.h"
#include "LSoundMgr.h"

class LGameScene : public SceneState
{
public:
	LSound* m_GameSound = nullptr;
public:
	float m_MapSizeX = 1500.0f;
	float m_MapSizeY = 300.0f;
public:
	float m_SceneDelaysStart = 0.0f;
	float m_SceneDelaysEnd = 1.0f;
public:
	LObject* m_pMapObj = nullptr;
	LObject* m_pFloor = nullptr;
	LObject* m_pDoor = nullptr;
	LPlayer* m_pPlayer = nullptr;
	LMonster* m_pMonster = nullptr;
	std::vector<LMonster*> m_MonsterList;
public:
	void ReleaseText();
public:
	bool PlayerInit();
	bool Init() override;
	void Process() override;
	void Release();
public:
	LGameScene(LScene* parent);
	virtual ~LGameScene();
};

