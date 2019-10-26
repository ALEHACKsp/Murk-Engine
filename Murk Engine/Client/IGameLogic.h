#pragma once

enum SceneNumbers
{
	Menu = -1
};

class IGameLogic
{
public:
	int Scene = Menu;

	void Update();
};

extern IGameLogic g_gameLogic;