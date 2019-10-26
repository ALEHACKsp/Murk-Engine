#include "IGameLogic.h"

#include "IClient.h"
#include "../Engine/IEngine.h"
#include "../Config/IConfig.h"
#include "IGameObject.h"

IGameObject LocalPlayer;
IGameObject Background;

void OnTestButtonPress()
{
	std::cout << "test button pressed\n";
}

void IGameLogic::Update()
{
	if (Scene == Menu)
	{
		g_client.ClearObjects();

		static bool bIsSceneInitialized = false;

		// main menu objects		
		static IGameObject TestButton;		

		if (!bIsSceneInitialized)
		{
			TestButton.bIsButton = true;
			TestButton.lpszName = (LPSTR)"TestButton";
			TestButton.lpszTexturePath = (LPSTR)"images\\button.jpg";
			TestButton.x = 100;
			TestButton.y = 100;
			TestButton.w = 184;
			TestButton.h = 146;
			TestButton.OnPress = (fnOnPress)OnTestButtonPress;
			TestButton.Initialize();

			Background.lpszName = (LPSTR)"Background";
			Background.lpszTexturePath = (LPSTR)"images\\background.jpg";
			Background.x = 0;
			Background.y = 0;
			Background.w = 1280;
			Background.h = 720;
			Background.Initialize();
			

			bIsSceneInitialized = true;
		}
		

		g_client.AddObject(Background);
		g_client.AddObject(TestButton);
	}
}