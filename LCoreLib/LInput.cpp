#include "LInput.h"

LVector LInput::GetWorldPos(float windowWidth, float windowHeight, float cameraPosX, float cameraPosY)
{
    float HalfWindowX = windowWidth * 0.5f;
    float HalfWindowY = windowHeight * 0.5f;
    LVector mouseLTPos = { cameraPosX - HalfWindowX,
                          cameraPosY + HalfWindowY, 1.0f };
    mouseLTPos.x = mouseLTPos.x + m_MousePos.x;
    mouseLTPos.y = mouseLTPos.y - m_MousePos.y;

    return mouseLTPos;
}

bool LInput::Init()
{
	return true;
}

bool LInput::Frame()
{
    ::GetCursorPos(&m_MousePos);
    ::ScreenToClient(g_hWnd, &m_MousePos);

    for (int ikey = 0; ikey < 256; ikey++)
    {
        SHORT s = GetAsyncKeyState(ikey);
        if (s & 0x8000)
        {
            if (m_dwKeyState[ikey] == DWORD(KeyState::KEY_FREE))
            {
                m_dwKeyState[ikey] = DWORD(KeyState::KEY_PUSH);
            }
            else
            {
                m_dwKeyState[ikey] = DWORD(KeyState::KEY_HOLD);
            }
        }
        else
        {
            if (m_dwKeyState[ikey] == DWORD(KeyState::KEY_HOLD)
            ||  m_dwKeyState[ikey] == DWORD(KeyState::KEY_PUSH))
            {
                m_dwKeyState[ikey] = DWORD(KeyState::KEY_UP);
            }
            else
            {
                m_dwKeyState[ikey] = DWORD(KeyState::KEY_FREE);
            }
        }
    }
	return true;
}

bool LInput::Render()
{
#ifdef _DEBUG
    /*std::wstring mousePos = std::to_wstring(m_MousePos.x);
    mousePos += L",";
    mousePos += std::to_wstring(m_MousePos.y);
    mousePos += L"\n";
    L_DebugString(mousePos.c_str());*/
#endif
	return true;
}

bool LInput::Release()
{
	return true;
}