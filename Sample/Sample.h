#include "LCore.h"
#include "LCamera.h"
#include "LPlaneObj.h"
#include "LPlayer.h"
#include "LMonster.h"
#include "LScene.h"
#pragma comment(lib, "LCoreLib.lib")

class Sample : public LCore
{
public:
	LScene* m_Scene = nullptr;
	ID3D11BlendState* m_AlphaBlend = nullptr;
	LObject* m_pMapObj = nullptr;
	LObject* m_pFloor = nullptr;
	LPlayer* m_pPlayer = nullptr;
	LMonster* m_pMonster = nullptr;
	std::vector<LMonster*> m_MonsterList;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	void CreateBlendState();
public:
	virtual ~Sample();
};

