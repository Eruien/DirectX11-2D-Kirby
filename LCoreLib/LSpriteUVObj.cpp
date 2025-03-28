#include "LSpriteUVObj.h"

void LSpriteUVObj::SetTarget(LVector& t)
{
    m_Target = t;
    m_fDirection = m_Target - m_vPosition;
    float fDistance = m_fDirection.Length();
    m_fDirection /= fDistance;
}

void LSpriteUVObj::SetUVAnimation(int spriteCount, float animationTime)
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

    m_OffsetTime = animationTime / m_UVList.size();
}

void LSpriteUVObj::SetUVPosition()
{
    LRectUV rectUV = m_UVList[m_AnimationIndex];
   
    m_VertexList[0].t.x = rectUV.m_Min.x;  m_VertexList[0].t.y = rectUV.m_Min.y;
    m_VertexList[1].t.x = rectUV.m_Max.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[2].t.x = rectUV.m_Min.x;  m_VertexList[2].t.y = rectUV.m_Max.y;

    m_VertexList[3].t.x = rectUV.m_Min.x;  m_VertexList[3].t.y = rectUV.m_Max.y;
    m_VertexList[4].t.x = rectUV.m_Max.x;  m_VertexList[4].t.y = rectUV.m_Min.y;
    m_VertexList[5].t.x = rectUV.m_Max.x;  m_VertexList[5].t.y = rectUV.m_Max.y;
}

void LSpriteUVObj::SetUVPositionReverse()
{
    LRectUV rectUV = m_UVList[m_AnimationIndex];

    m_VertexList[0].t.x = rectUV.m_Max.x;  m_VertexList[0].t.y = rectUV.m_Min.y;
    m_VertexList[1].t.x = rectUV.m_Min.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[2].t.x = rectUV.m_Max.x;  m_VertexList[2].t.y = rectUV.m_Max.y;

    m_VertexList[3].t.x = rectUV.m_Max.x;  m_VertexList[2].t.y = rectUV.m_Max.y;
    m_VertexList[4].t.x = rectUV.m_Min.x;  m_VertexList[1].t.y = rectUV.m_Min.y;
    m_VertexList[5].t.x = rectUV.m_Min.x;  m_VertexList[5].t.y = rectUV.m_Max.y;
}

bool LSpriteUVObj::Init()
{
    return true;
}

bool LSpriteUVObj::Frame()
{
    SetBox(m_vPosition, m_vScale.x * 2, m_vScale.y * 2, 1.0f);

    LPlaneObj::Frame();

    m_AnimationElapsed += g_fSPF;

    if (m_AnimationElapsed >= m_OffsetTime)
    {
        m_AnimationIndex++;

        if (m_AnimationIndex >= m_UVList.size())
        {
            m_AnimationIndex = 0;
            m_AnimationElapsed = 0;
        }

        m_AnimationElapsed -= m_OffsetTime;
    }

    return true;
}

bool LSpriteUVObj::Render()
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



bool LSpriteUVObj::Release()
{
    return true;
}

LSpriteUVObj::LSpriteUVObj() {}
