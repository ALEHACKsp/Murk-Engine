#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

typedef void(__stdcall* fnOnPress)();

class CGameObject
{
public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;

	LPSTR m_lpszName = nullptr;
	bool m_bIsText = 0;
	bool m_bIsPlayer = 0;
	bool m_bIsEntity = 0;
	bool m_bIsEnemy = 0;
	bool m_bIsButton = 0;
	bool m_bIsPressed = 0;
	bool m_bIsCheckbox = 0;
	bool* m_pCheckboxBool = nullptr;
	bool m_bIsActive = false;
	bool m_bShouldBeRendered = true;

	LPSTR m_lpszTexturePath = 0;
	LPDIRECT3DTEXTURE9 m_lpTexture = 0;
	LPD3DXSPRITE m_lpSprite = 0;

	void Initialize( );
	void Render( );

	fnOnPress m_pOnPress = nullptr;
};