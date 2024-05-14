#pragma once
#include "LScene.h"

class LEndScene : public SceneState
{
public:
	float m_MapSizeX = 400.0f;
	float m_MapSizeY = 300.0f;
public:
	LPlaneObj* m_pMapObj = nullptr;
	LPlaneObj* m_pStartButton = nullptr;
public:
	bool Init() override;
	void Process() override;
	void Release();
public:
	LEndScene(LScene* parent);
	virtual ~LEndScene();
};

