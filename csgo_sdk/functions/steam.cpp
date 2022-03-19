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
	if (!SteamAPI_Init()) {
		Utils::ConsolePrint("Error\n");
	}
	Utils::ConsolePrint("start\n");
	
	SteamAPI_RunCallbacks();
	Utils::ConsolePrint("start\n");
	printf("Getting Number of Current Players\n");
	for (int i = 0; i < 100; i++) {
		SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(k_ELobbyTypePublic, 10);
		m_NumberOfCurrentPlayersCallResult.Set(hSteamAPICall, this, &CGameManager::OnGetNumberOfCurrentPlayers);
	
		
	//Utils::ConsolePrint( SteamUserStats()->get(hSteamAPICall));
	}
}

// Вызывается, когда SteamUserStats()->GetNumberOfCurrentPlayers() возвращается асинхронно, после вызова SteamAPI_RunCallbacks().
void CGameManager::OnGetNumberOfCurrentPlayers(NumberOfCurrentPlayers_t* pCallback, bool bIOFailure)
{
	if (bIOFailure || !pCallback->m_bSuccess)
	{
		Utils::ConsolePrint("error");
		return;
	}

	printf("Number of players currently playing: %d\n", pCallback->m_cPlayers);
	Utils::ConsolePrint("success");
}