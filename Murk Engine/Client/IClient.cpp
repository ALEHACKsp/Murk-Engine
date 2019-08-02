#include "IClient.h"

int IClient::AddObject(IGameObject obj)
{
	Objects.push_back(obj);
	return Objects.size();
}

void IClient::ClearObjects()
{
	Objects.clear();
}