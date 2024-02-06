// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CgameCharacter.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CGAME_API ABaseCharacter : public ACgameCharacter
{
	GENERATED_BODY()

public:
	// Default Class constructor
	ABaseCharacter();

	// Called when init Character
	virtual void setCharacterStats();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// ingame character stats
	int health;
	int maxHealth;
	int damage;
	int level;
	int superRechargeProgress;
	int speed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
