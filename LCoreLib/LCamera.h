#pragma once
#include "LStd.h"

class LCamera
{
public:
    float m_HalfMapX = 0.0f;
    float m_HalfMapY = 0.0f;
public:
    LMatrix m_matView;
    LMatrix m_matOrthoProjection;
    LMatrix m_matProj;
    LVector m_vCameraPos;
    DWORD m_dwWindowWidth;
    DWORD m_dwWindowHeight;
public:
    LMatrix   CreateLookAt(LVector p, LVector t, LVector n = { 0,1,0 });
    LMatrix   CreatePerspectiveFov(float fFov, float fAspect, float fNear, float fFar);
public:
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
public:
    void Create(LVector pos, LVector2 size);
public:
    virtual ~LCamera() {}
};

