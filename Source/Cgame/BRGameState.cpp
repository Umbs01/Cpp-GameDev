// Fill out your copyright notice in the Description page of Project Settings.

#include "BRGameState.h"
#include "Net/UnrealNetWork.h"

ABRGameState::ABRGameState()
{
	ConnectedPlayers = 0;
	CurrentPlayers = ConnectedPlayers;
}

void ABRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABRGameState, CurrentPlayers);
}

void ABRGameState::OnRep_CurrentPlayers()
{
	UE_LOG(LogTemp, Warning, TEXT("client: %d players remaining"), CurrentPlayers);
}

void ABRGameState::PlayerDied()
{
	CurrentPlayers--;
	UE_LOG(LogTemp, Warning, TEXT("server: %d players remaining"), CurrentPlayers);
}

