#include "IGameLogic.h"

#include "IClient.h"
#include "../Engine/IEngine.h"
#include "../Config/IConfig.h"
#include "IGameObject.h"

IGameObject LocalPlayer;
IGameObject Background;

void IGameLogic::Update()
{
	if (Scene == -1)
	{
		g_client.ClearObjects();

		static bool IsSceneInitialized = false;

		if (!IsSceneInitialized)
		{
			LocalPlayer.IsEntity = true;
			LocalPlayer.IsPlayer = true;
			LocalPlayer.w = 124;
			LocalPlayer.h = 76;
			LocalPlayer.x = 640;
			LocalPlayer.y = 360;
			LocalPlayer.lpszTexturePath = (LPSTR)"images/localplayer.png";
			LocalPlayer.Initialize();

			IsSceneInitialized = true;
		}

		if (IsKeyPressed(VK_W))
		{
			if (LocalPlayer.y > 0) LocalPlayer.y -= 3;
		}

		if (IsKeyPressed(VK_A))
		{
			if (LocalPlayer.x > 0) LocalPlayer.x -= 3;
		}

		if (IsKeyPressed(VK_S))
		{
			if (LocalPlayer.y + LocalPlayer.h < g_config.Settings.height) LocalPlayer.y += 3;
		}

		if (IsKeyPressed(VK_D))
		{
			if (LocalPlayer.x + LocalPlayer.w < g_config.Settings.width) LocalPlayer.x += 3;
		}

		g_client.AddObject(LocalPlayer);
	}
}