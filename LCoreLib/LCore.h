#pragma once
#include "LDevice.h"
#include "LTimer.h"
#include "LInput.h"
#include "LCamera.h"
#include "LManager.h"
#include "LManagerAgr.h"
#include "LWrite.h"

class LCore : public LDevice
{
public:
	std::shared_ptr<LCamera> m_pMainCamera = nullptr;
	LTimer m_Gametimer;
	//LCamera* m_pMainCamera;
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool Run();
private:
	bool EngineInit();
	bool EngineFrame();
	bool EngineRender();
	bool EngineRelease();
public:
	virtual ~LCore();
};

