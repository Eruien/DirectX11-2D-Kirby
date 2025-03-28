#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <queue>
#include <codecvt>
#include "LUtils.h"

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "DirectXTex.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment (lib, "DirectXTex.lib")

static float g_fMapSizeX = 400.0f;
static float g_fMapSizeY = 300.0f;

static void L_DebugString(const WCHAR* msg)
{
#ifdef _DEBUG
	OutputDebugString(msg);
#endif
}

static std::string wtm(std::wstring str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
	return conv.to_bytes(str);
}

extern HWND g_hWnd;
extern float g_fGameTimer;
extern float g_fSPF;
extern int g_WindowWidth;
extern int g_WindowHeight;
