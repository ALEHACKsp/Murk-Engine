#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

typedef void(__stdcall* fnOnPress)();

class IGameObject
{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	LPSTR lpszName;
	bool bIsText = 0;
	bool bIsPlayer = 0;
	bool bIsEntity = 0;
	bool bIsEnemy = 0;
	bool bIsButton = 0;
	bool bIsPressed = 0;
	bool bIsCheckbox = 0;
	bool* CheckboxBool = nullptr;
	bool bIsActive = 0;
	bool bShouldBeRendered = 1;

	LPSTR lpszTexturePath = 0;
	LPDIRECT3DTEXTURE9 lpTexture = 0;
	LPD3DXSPRITE lpSprite = 0;

	void Initialize();
	void Render();

	fnOnPress OnPress = nullptr;
};