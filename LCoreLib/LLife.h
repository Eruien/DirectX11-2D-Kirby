#pragma once
#include "LPlaneObj.h"

class LLife : public LPlaneObj
{
public:
	std::vector<LRectUV> m_UVList;
	int m_AnimationIndex = 0;
	bool m_IsDead = false;
public:
	void SetUVAnimation(int spriteCount, float animationTime);
	void SetUVPosition();
	void SetUVPositionReverse();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	LLife();
};

