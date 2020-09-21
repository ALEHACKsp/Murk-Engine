#pragma once

enum SceneNumbers
{
	Menu = -1
};

class CGameLogic
{
public:
	int m_iScene = Menu;

	void Think( );
};

inline CGameLogic* g_pGameLogic = new CGameLogic;