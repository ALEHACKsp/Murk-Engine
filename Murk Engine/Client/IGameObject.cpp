#include "IGameObject.h"
#include "..\Engine\IEngine.h"

#include <Windows.h>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>

void IGameObject::Initialize()
{
	if (D3DXCreateTextureFromFileExA(g_window.pDevice, lpszTexturePath, w, h, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &lpTexture) != D3D_OK)
	{
		Msg("Failed to initialize textures");
		PostQuitMessage(0);
		return;
	}

	if (!SUCCEEDED(D3DXCreateSprite(g_window.pDevice, &lpSprite)))
	{
		Msg("Failed to initialize textures");
		PostQuitMessage(0);
		return;
	}
}

void IGameObject::Render()
{
	if (lpSprite && lpTexture && IsShouldBeRendered)
	{
		lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 v;
		v.x = this->x;
		v.y = this->y;
		v.z = 0;
		lpSprite->Draw(lpTexture, 0, 0, &v, D3DCOLOR_ARGB(255, 255, 255, 255));
		lpSprite->End();

		if (IsButton)
		{
			POINT pos;

			pos.x = g_window.mousex;
			pos.y = g_window.mousey;

			if (GetAsyncKeyState(0x1) && pos.x >= this->x && pos.x <= this->x + this->w &&
				pos.y >= this->y && pos.y <= this->y + this->h && GetForegroundWindow() == FindWindow(ClassName, 0))
				IsPressed = true;
		}

		if (IsCheckbox)
		{
			POINT pos;

			pos.x = g_window.mousex;
			pos.y = g_window.mousey;

			if (GetAsyncKeyState(0x1) && pos.x >= this->x && pos.x <= this->x + this->w &&
				pos.y >= this->y && pos.y <= this->y + this->h && GetForegroundWindow() == FindWindow(ClassName, 0))
				* CheckboxBool = !*CheckboxBool;
		}
	}
}