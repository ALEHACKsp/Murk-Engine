#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

class IGameObject
{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	bool IsText = 0;
	bool IsPlayer = 0;
	bool IsEntity = 0;
	bool IsEnemy = 0;
	bool IsButton = 0;
	bool IsPressed = 0;
	bool IsCheckbox = 0;
	bool* CheckboxBool = nullptr;
	bool IsActive = 0;
	bool IsShouldBeRendered = 1;

	LPSTR lpszTexturePath = 0;
	LPDIRECT3DTEXTURE9 lpTexture = 0;
	LPD3DXSPRITE lpSprite = 0;

	void Initialize();
	void Render();
};