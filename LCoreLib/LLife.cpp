#include "LLife.h"

void LLife::SetUVAnimation(int spriteCount, float animationTime)
{
    LRectUV rectUV;
    LVector uv;

    float offset = 1.0f / float(spriteCount);

    for (int i = 0; i < spriteCount; i++)
    {
        uv.x = i * offset;
        uv.y = 0 * offset;
        rectUV.m_Min = uv;

        rectUV.m_Max.x = uv.x + offset;
        rectUV.m_Max.y = 1.0f;
        m_UVList.push_back(rectUV);
    }
}

void LLife::SetUVPosition()
{
    LRectUV rectUV = m_UVList[m_AnimationIndex];

    m_VertexList[0].t.x = rectUV.m_Min.x;  m_VertexList[0].t.y = rectUV.m_Min.y;
    m_VertexList[1].t.x = rectUV.m_Max.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[2].t.x = rectUV.m_Min.x;  m_VertexList[2].t.y = rectUV.m_Max.y;

    m_VertexList[3].t.x = rectUV.m_Min.x;  m_VertexList[3].t.y = rectUV.m_Max.y;
    m_VertexList[4].t.x = rectUV.m_Max.x;  m_VertexList[4].t.y = rectUV.m_Min.y;
    m_VertexList[5].t.x = rectUV.m_Max.x;  m_VertexList[5].t.y = rectUV.m_Max.y;
}

void LLife::SetUVPositionReverse()
{
    LRectUV rectUV = m_UVList[m_AnimationIndex];

    m_VertexList[0].t.x = rectUV.m_Max.x;  m_VertexList[0].t.y = rectUV.m_Min.y;
    m_VertexList[1].t.x = rectUV.m_Min.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[2].t.x = rectUV.m_Max.x;  m_VertexList[2].t.y = rectUV.m_Max.y;

    m_VertexList[3].t.x = rectUV.m_Max.x;  m_VertexList[2].t.y = rectUV.m_Max.y;
    m_VertexList[4].t.x = rectUV.m_Min.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[5].t.x = rectUV.m_Min.x;  m_VertexList[5].t.y = rectUV.m_Max.y;
}

bool LLife::Init()
{
    return true;
}

bool LLife::Frame()
{
    SetBox(m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);
    
    if (m_AnimationIndex == m_UVList.size() - 1)
    {
        m_IsDead = true;
        m_AnimationIndex = 0;
    }
    LPlaneObj::Frame();

    return true;
}

bool LLife::Render()
{
    LRectUV rectUV = m_UVList[m_AnimationIndex];

    m_VertexList[0].t.x = rectUV.m_Min.x;  m_VertexList[0].t.y = rectUV.m_Min.y;
    m_VertexList[1].t.x = rectUV.m_Max.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[2].t.x = rectUV.m_Min.x;  m_VertexList[2].t.y = rectUV.m_Max.y;

    m_VertexList[3].t.x = rectUV.m_Min.x;  m_VertexList[3].t.y = rectUV.m_Max.y;
    m_VertexList[4].t.x = rectUV.m_Max.x;  m_VertexList[4].t.y = rectUV.m_Min.y;
    m_VertexList[5].t.x = rectUV.m_Max.x;  m_VertexList[5].t.y = rectUV.m_Max.y;

    m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, 0, nullptr, &m_VertexList.at(0), 0, 0);
    PreRender();
    PostRender();
    return true;
}



bool LLife::Release()
{
    return true;
}

LLife::LLife() {}
