#include "Engine/CEngine.h"
#include "Config/CConfig.h"
#include "Client/CClient.h"
#include "Client/CGameObject.h"
#include "Client/CGameLogic.h"

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

BOOL WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, int )
{
#ifdef _DEBUG
	AllocConsole( );
	AttachConsole( GetCurrentProcessId( ) );
	freopen( "CON", "w", stdout );
#endif
	if ( !g_pWindow->InitializeWindow( ) ) return 1;

	if ( !g_pWindow->InitializeDevice( ) )
	{
		g_pWindow->DeleteWindow( );
		return 1;
	}

	g_pConfig->Initialize( );

	ShowWindow( g_pWindow->m_hWindow, SW_SHOWDEFAULT );
	UpdateWindow( g_pWindow->m_hWindow );

	MSG msg;
	ZeroMemory( &msg, sizeof( MSG ) );

	while ( msg.message != WM_QUIT )
	{
		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessageA( &msg );
			continue;
		}

		g_pWindow->m_pDevice->Clear( 0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 255, 255, 255, 255 ), 1.0f, 0 );
		if ( g_pWindow->m_pDevice->BeginScene( ) >= 0 )
		{
			for ( auto& c : g_pClient->m_vecObjects )
				c.Render( );

			g_pWindow->m_pDevice->EndScene( );
		}

		HRESULT hr = g_pWindow->m_pDevice->Present( 0, 0, 0, 0 );
		if ( hr == D3DERR_DEVICELOST && g_pWindow->m_pDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET )
			g_pWindow->ResetDevice( );

		g_pGameLogic->Think( );
	}

	g_pConfig->ResetResolution( );
	g_pWindow->DeleteWindow( );

	return 0;
}