// Fill out your copyright notice in the Description page of Project Settings.


#include "BRGameMode.h"
#include "BRGameState.h"
#include "BRGameState.h"

ABRGameMode::ABRGameMode()
{
	// set default game state class
	GameStateClass = ABRGameState::StaticClass();

	// set default pawn class to our Blueprinted Basecharacter
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_Barbarian"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

// get the number of players connected
int ABRGameMode::GetConnectedPlayers()
{
	return GetGameState<ABRGameState>()->ConnectedPlayers;
}

// set the number of players connected
void ABRGameMode::SetConnectedPlayers(int deltaPlayer)
{
	GetGameState<ABRGameState>()->ConnectedPlayers = deltaPlayer;
}

// get the number of remaining players in the match
int ABRGameMode::GetCurrentPlayers()
{
	return GetGameState<ABRGameState>()->CurrentPlayers;
}

// set the number of remaining players in the match
void ABRGameMode::SetCurrentPlayers(int deltaPlayer)
{
	GetGameState<ABRGameState>()->CurrentPlayers = deltaPlayer;
}

void ABRGameMode::PlayerDied()
{
	if (ABRGameState* GS = GetGameState<ABRGameState>())
	{
		GS->PlayerDied();
	}
}
