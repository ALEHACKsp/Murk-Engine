#include "CEngine.h"
#include "../Config/CConfig.h"

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

LRESULT WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_LBUTTONDOWN:
			g_pWindow->m_posMouse.x = LOWORD( lParam );
			g_pWindow->m_posMouse.y = HIWORD( lParam );
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

bool CWindow::InitializeWindow( )
{
	m_hInst = GetModuleHandleA( nullptr );

	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	wc.cbSize = sizeof( WNDCLASSEX );
	wc.style = CS_CLASSDC;
	wc.hInstance = m_hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = ClassName;

	if ( !RegisterClassEx( &wc ) )
	{
		Msg( "Error during creating window!" );
		return false;
	}

	m_hWindow = CreateWindowA( wc.lpszClassName, WindowName, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 1280, 720, 0, 0, wc.hInstance, 0 );
	if ( !m_hWindow )
	{
		Msg( "Error during creating window!" );
		UnregisterClassA( ClassName, m_hInst );
		return false;
	}

	m_lpszClassName = ( LPSTR )ClassName;

	return true;
}

void CWindow::DeleteWindow( )
{
	CleanupDevice( );
	DestroyWindow( m_hWindow );
	UnregisterClass( m_lpszClassName, m_hInst );
}

bool CWindow::InitializeDevice( )
{
	m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if ( !m_pD3D )
	{
		Msg( "Error during initializing DirectX Device!" );
		return false;
	}

	ZeroMemory( &m_D3Dpp, sizeof( m_D3Dpp ) );
	m_D3Dpp.Windowed = TRUE;
	m_D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	m_D3Dpp.EnableAutoDepthStencil = TRUE;
	m_D3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	if ( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3Dpp, &m_pDevice ) < 0 )
	{
		Msg( "Error during initializing DirectX Device!" );
		return false;
	}

	return true;
}

void CWindow::CleanupDevice( )
{
	if ( m_pDevice ) m_pDevice->Release( );
	if ( m_pD3D ) m_pD3D->Release( );
}

void CWindow::ResetDevice( )
{
	m_pDevice->Reset( &m_D3Dpp );
}