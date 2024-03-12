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
	FString deathMessage = FString::Printf(TEXT("client: %d players remaining"), CurrentPlayers);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
}

void ABRGameState::PlayerDied()
{
	if (HasAuthority())
	{
		CurrentPlayers--;
		UE_LOG(LogTemp, Warning, TEXT("server: %d players remaining"), CurrentPlayers);
	}
}

