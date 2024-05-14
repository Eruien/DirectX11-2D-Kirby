#pragma once
#include "LScene.h"
#include "LPlayer.h"
#include "LMonster.h"
#include "LBoss.h"
#include "LSoundMgr.h"

class LBossScene : public SceneState
{
public:
	LSound* m_GameSound = nullptr;
public:
	float m_MonsterSpawnTime = 20.0f;
	float m_MonsterSpawnTimeStart = 0.0f;
public:
	float m_MapSizeX = 400.0f;
	float m_MapSizeY = 300.0f;
public:
	float m_SceneDelaysStart = 0.0f;
	float m_SceneDelaysEnd = 1.0f;
public:
	LObject* m_pMapObj = nullptr;
	LObject* m_pFloor = nullptr;
	LPlayer* m_pPlayer = nullptr;
	LMonster* m_pMonster = nullptr;
	std::vector<LMonster*> m_MonsterList;
	LBoss* m_pBoss = nullptr;
public:
	void CreateTwoMonster();
public:
	bool Init() override;
	void Process() override;
	void Release();
public:
	LBossScene(LScene* parent);
	virtual ~LBossScene();
};

