#include "../sdk/utils/utils.hpp"
#include "../headers/isteammatchmaking.h"
#include "../headers/steam_api.h"



#pragma comment( lib, "steam_api.lib" )

class CCreateLobby
{
public:
	CCallResult<CCreateLobby, LobbyMatchList_t> m_SteamCallResultLobbyMatchList;

	CCreateLobby();

	void Create(CCallResult<CCreateLobby, LobbyMatchList_t> m_SteamCallResultLobbyMatchList);

};

class CGameManager
{
public:
	void GetNumberOfCurrentPlayers();

private:
	void OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure);
	CCallResult<CGameManager, NumberOfCurrentPlayers_t> m_NumberOfCurrentPlayersCallResult;
};