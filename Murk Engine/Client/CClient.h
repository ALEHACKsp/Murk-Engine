#pragma once

#include <Windows.h>
#include <vector>

#include "CGameObject.h"

using std::vector;

class CClient
{
public:
	vector<CGameObject> m_vecObjects;

	int AddObject( CGameObject );
	void ClearObjects( );
};

inline CClient* g_pClient;