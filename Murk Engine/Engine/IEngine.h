#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <stdio.h>

#define Msg(x) MessageBoxA(0, x, "Murk Engine", MB_ICONERROR)
#define Print(x) printf(x)
#define IsKeyPressed(x) GetAsyncKeyState(x)

#define ClassName "murk_engine"
#define WindowName "Murk Engine"
#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

class IWindow
{
public:
	HWND hWindow;
	LPSTR lpszClassName;
	HINSTANCE hInst;

	int mousex = 0, mousey = 0;

	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3D9 pD3D;
	D3DPRESENT_PARAMETERS d3dpp;

	bool InitializeWindow(const char*, const char*, HINSTANCE);
	void DeleteWindow();

	bool InitializeDevice();
	void CleanupDevice();
	void ResetDevice();
};

extern IWindow g_window;