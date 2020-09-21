#include "CConfig.h"
#include "../Engine/CEngine.h"

#include <Windows.h>
#include <shlobj.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template<typename T = int>
T ReadString( const char* m_szPath, string m_szStr )
{
	ifstream m_iFile( m_szPath );

	string m_szBuf;
	while ( getline( m_iFile, m_szBuf ) )
	{
		if ( m_szBuf.find( m_szStr.c_str( ) ) != string::npos )
		{
			m_szBuf.erase( 0, m_szStr.length( ) );
			m_iFile.close( );

			stringstream ss;
			ss << m_szBuf;
			T ret;
			ss >> ret;
			return ret;
		}
	}

	m_iFile.close( );
	return {};
}

void CConfig::Initialize( )
{
	HWND desktop = GetDesktopWindow( );
	RECT rc;
	GetWindowRect( desktop, &rc );

	w = rc.right;
	h = rc.bottom;

	char szDocumentsPath[ MAX_PATH ];
	SHGetFolderPath( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, szDocumentsPath );

	m_szConfig = szDocumentsPath;
	m_szConfig += "\\Without Regrets";

	CreateDirectory( m_szConfig.c_str( ), 0 );

	m_szConfig += "\\settings.ini";

	m_Settings.m_nWidth = ReadString( m_szConfig.c_str( ), "resolution_w=" );
	m_Settings.m_nHeight = ReadString( m_szConfig.c_str( ), "resolution_h=" );
	m_Settings.m_bWindowed = ReadString<bool>( m_szConfig.c_str( ), "resolution_windowed=" );

	if ( !m_Settings.m_nWidth || !m_Settings.m_nHeight )
	{
		ofstream m_oFile( m_szConfig );
		m_oFile << "resolution_w=" << 1280 << endl;
		m_oFile << "resolution_h=" << 720 << endl;
		m_oFile << "resolution_windowed=" << false << endl;
		m_oFile.close( );
	}
}

void CConfig::ApplySettings( )
{
	/*DEVMODE dm;
	dm.dmSize = sizeof(dm);

	if (!Settings.windowed)
	{
		dm.dmPelsWidth = Settings.width;
		dm.dmPelsHeight = Settings.height;
	}
	else
	{
		dm.dmPelsWidth = w;
		dm.dmPelsHeight = h;
	}

	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);

	SetWindowPos(g_pWindow->hWindow, 0, 0, 0, dm.dmPelsWidth, dm.dmPelsHeight, 0);*/

	ofstream file( m_szConfig );

	file << "resolution_w=" << m_Settings.m_nWidth << endl;
	file << "resolution_h=" << m_Settings.m_nHeight << endl;
	file << "resolution_windowed=" << m_Settings.m_bWindowed << endl;

	file.close( );
}

void CConfig::ResetResolution( )
{
	DEVMODE dm;
	dm.dmSize = sizeof( dm );
	dm.dmPelsWidth = w;
	dm.dmPelsHeight = h;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings( &dm, CDS_UPDATEREGISTRY );
}