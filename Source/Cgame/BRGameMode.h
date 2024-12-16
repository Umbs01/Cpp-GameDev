// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BRGameMode.generated.h"


UCLASS()
class CGAME_API ABRGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABRGameMode();
	virtual ~ABRGameMode() = default;

	// get the number of players connected
	UFUNCTION(BlueprintPure, Category = "Players")
	int GetConnectedPlayers();

	// set the number of players connected
	UFUNCTION(BlueprintCallable, Category = "Players")
	void SetConnectedPlayers(int deltaplayer);

	// get the number of remaining players in the match
	UFUNCTION(BlueprintPure, Category = "Players")
	int GetCurrentPlayers();

	// set the number of remaining players in the match
	UFUNCTION(BlueprintCallable, Category = "Players")
	void SetCurrentPlayers(int deltaplayer);

	// called when player dies
	UFUNCTION(BlueprintCallable, Category = "Players")
	void PlayerDied();
};

