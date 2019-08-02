#pragma once

class IGameLogic
{
public:
	int Scene = -1;

	void Update();
};

extern IGameLogic g_gameLogic;