#pragma once

#include <Windows.h>
#include <vector>

#include "IGameObject.h"

using std::vector;

class IClient
{
public:
	vector<IGameObject> Objects;

	int AddObject(IGameObject);
	void ClearObjects();
};

extern IClient g_client;