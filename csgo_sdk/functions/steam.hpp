#include "../sdk/utils/utils.hpp"
#include "../headers/isteammatchmaking.h"
#include "../headers/steam_api.h"



#pragma comment( lib, "steam_api.lib" )

class CGameManager
{
public:
	void GetNumberOfCurrentPlayers();

	void OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure);
	CCallResult<CGameManager, NumberOfCurrentPlayers_t> m_NumberOfCurrentPlayersCallResult;
};