#pragma once

#include <string>

class CConfig
{
public:
	struct
	{
		int m_nWidth = 1280;
		int m_nHeight = 720;
		bool m_bWindowed = true;
	} m_Settings;

	int w, h;

	std::string m_szConfig;

	void Initialize( );
	void ApplySettings( );
	void ResetResolution( );
};

inline CConfig* g_pConfig = new CConfig;