// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BRGameState.generated.h"

/**
 * 
 */
UCLASS()
class CGAME_API ABRGameState : public AGameState
{
	GENERATED_BODY()

public:
	ABRGameState();
	virtual ~ABRGameState() = default;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int ConnectedPlayers;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentPlayers)
	int CurrentPlayers;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void PlayerDied();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void OnRep_CurrentPlayers();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
