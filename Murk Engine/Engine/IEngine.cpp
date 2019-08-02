#include "IEngine.h"
#include "../Config/IConfig.h"

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		g_window.mousex = LOWORD(lParam);
		g_window.mousey = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool IWindow::InitializeWindow(const char* szWindowName, const char* szClassName, HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = szClassName;

	if (!RegisterClassEx(&wc))
	{
		Msg("Error during creating window!");
		return false;
	}

	hWindow = ::CreateWindow(wc.lpszClassName, szWindowName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 1280, 720, 0, 0, wc.hInstance, 0);
	if (!hWindow)
	{
		Msg("Error during creating window!");
		::UnregisterClass(szClassName, hInstance);
		return false;
	}

	lpszClassName = (LPSTR)szClassName;
	hInst = hInstance;

	return true;
}

void IWindow::DeleteWindow()
{
	CleanupDevice();
	::DestroyWindow(hWindow);
	::UnregisterClass(lpszClassName, hInst);
}

bool IWindow::InitializeDevice()
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
	{
		Msg("Error during initializing DirectX Device!");
		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &pDevice) < 0)
	{
		Msg("Error during initializing DirectX Device!");
		return false;
	}

	return true;
}

void IWindow::CleanupDevice()
{
	if (pDevice) { pDevice->Release(); pDevice = NULL; }
	if (pD3D) { pD3D->Release(); pD3D = NULL; }
}

void IWindow::ResetDevice()
{
	pDevice->Reset(&d3dpp);
}