#include "../sdk/utils/utils.hpp"
#include "../headers/isteammatchmaking.h"
#include "../headers/steam_api.h"
#include "steam.hpp"


#pragma comment( lib, "steam_api.lib" )
#pragma once



// Сделайте асинхронный запрос на получение числа активных игроков.
void CGameManager::GetNumberOfCurrentPlayers()
{
	SteamAPI_Init();
	Utils::ConsolePrint("start");
	printf("Getting Number of Current Players\n");
	SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 10);
	m_NumberOfCurrentPlayersCallResult.Set(hSteamAPICall, this, &CGameManager::OnGetNumberOfCurrentPlayers);
}

// Вызывается, когда SteamUserStats()->GetNumberOfCurrentPlayers() возвращается асинхронно, после вызова SteamAPI_RunCallbacks().
void CGameManager::OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure)
{
	if (bIOFailure || !pCallback->m_bSuccess)
	{
		printf("NumberOfCurrentPlayers_t failed!\n");
		Utils::ConsolePrint("error");
		return;
	}

	printf("Number of players currently playing: %d\n", pCallback->m_cPlayers);
}