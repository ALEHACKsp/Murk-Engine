#include "Engine/IEngine.h"
#include "Config/IConfig.h"
#include "Client/IClient.h"
#include "Client/IGameObject.h"
#include "Client/IGameLogic.h"

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

IWindow g_window;
IClient g_client;
IGameLogic g_gameLogic;
IConfig g_config;

BOOL WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
#endif
	if (!g_window.InitializeWindow(WindowName, ClassName, hInst)) return 1;

	if (!g_window.InitializeDevice())
	{
		g_window.DeleteWindow();
		return 1;
	}

	g_config.Initialize();

	ShowWindow(g_window.hWindow, SW_SHOWDEFAULT);
	UpdateWindow(g_window.hWindow);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		g_window.pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
		if (g_window.pDevice->BeginScene() >= 0)
		{
			for (auto c : g_client.Objects)
				c.Render();

			g_window.pDevice->EndScene();
		}

		HRESULT hr = g_window.pDevice->Present(0, 0, 0, 0);
		if (hr == D3DERR_DEVICELOST && g_window.pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			g_window.ResetDevice();

		g_gameLogic.Update();
	}
	
	g_config.ResetResolution();
	g_window.DeleteWindow();

	return 0;
}