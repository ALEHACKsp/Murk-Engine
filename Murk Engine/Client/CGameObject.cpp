#include "CGameObject.h"
#include "..\Engine\CEngine.h"

#include <Windows.h>
#include <iostream>

#include <d3d9.h>
#include <d3dx9.h>

void CGameObject::Initialize( )
{
	if ( D3DXCreateTextureFromFileExA( g_pWindow->m_pDevice, m_lpszTexturePath, w, h, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, 0, 0, &m_lpTexture ) != D3D_OK )
	{
		Msg( "Failed to initialize textures" );
		PostQuitMessage( 0 );
		return;
	}

	if ( !SUCCEEDED( D3DXCreateSprite( g_pWindow->m_pDevice, &m_lpSprite ) ) )
	{
		Msg( "Failed to initialize textures" );
		PostQuitMessage( 0 );
		return;
	}
}

void CGameObject::Render( )
{
	if ( m_lpSprite && m_lpTexture && m_bShouldBeRendered )
	{
		m_lpSprite->Begin( D3DXSPRITE_ALPHABLEND );
		D3DXVECTOR3 v;
		v.x = this->x;
		v.y = this->y;
		v.z = 0;
		m_lpSprite->Draw( m_lpTexture, 0, 0, &v, D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
		m_lpSprite->End( );

		if ( m_bIsButton )
		{
			static DWORD dwTime;
			if ( GetTickCount64( ) - dwTime < 250 )
				return;

			POINT pos;

			pos.x = g_pWindow->m_posMouse.x;
			pos.y = g_pWindow->m_posMouse.y;

			if ( GetAsyncKeyState( 0x1 ) && pos.x >= this->x && pos.x <= this->x + this->w &&
				pos.y >= this->y && pos.y <= this->y + this->h && GetForegroundWindow( ) == FindWindow( ClassName, 0 ) )
			{
				if ( m_pOnPress ) m_pOnPress( );
				m_bIsPressed = true;
				dwTime = GetTickCount64( );
			}
		}

		if ( m_bIsCheckbox )
		{
			static DWORD dwTime;
			if ( GetTickCount64( ) - dwTime < 250 )
				return;

			POINT pos;

			pos.x = g_pWindow->m_posMouse.x;
			pos.y = g_pWindow->m_posMouse.y;

			if ( GetAsyncKeyState( 0x1 ) && pos.x >= this->x && pos.x <= this->x + this->w &&
				pos.y >= this->y && pos.y <= this->y + this->h && GetForegroundWindow( ) == FindWindow( ClassName, 0 ) )
			{
				if ( m_pCheckboxBool ) *m_pCheckboxBool = !*m_pCheckboxBool;
				dwTime = GetTickCount64( );
			}
		}
	}
}