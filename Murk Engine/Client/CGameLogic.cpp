#include "CGameLogic.h"

#include "CClient.h"
#include "../Engine/CEngine.h"
#include "../Config/CConfig.h"
#include "CGameObject.h"

#include <iostream>
#include <mutex>

namespace GlobalObjects
{
	CGameObject m_oBackground;
	CGameObject m_oLocalPlayer;
}

void CGameLogic::Think()
{
	if (m_iScene == Menu)
	{
		g_pClient->ClearObjects();

		std::once_flag m_fMutex;
		std::call_once( m_fMutex,
			[ ] ( ) -> void
			{
				// initialize objects
			}
		);

		g_pClient->AddObject( GlobalObjects::m_oBackground );
		g_pClient->AddObject( GlobalObjects::m_oLocalPlayer );
	}
}