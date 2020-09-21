#include "CClient.h"

int CClient::AddObject( CGameObject m_oObj )
{
	m_vecObjects.push_back( m_oObj );
	return m_vecObjects.size( );
}

void CClient::ClearObjects( )
{
	m_vecObjects.clear( );
}