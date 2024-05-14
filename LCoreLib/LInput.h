#pragma once
#include "LStd.h"

enum class KeyState
{
	KEY_FREE = 0,
	KEY_UP = 1,
	KEY_PUSH = 2,
	KEY_HOLD = 3,
};

class LInput
{
public:
	static LInput& GetInstance()
	{
		static LInput input;
		return input;
	}
public:
	POINT m_MousePos;
	DWORD m_dwKeyState[256] = {0,};
public:
	LVector GetWorldPos(float windowWidth, float windowHeight, float cameraPosX, float cameraPosY);
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
private:
	LInput() {}
public:
	~LInput() {}
};

