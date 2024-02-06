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

	virtual void setCharacterStats();

protected:
	// ingame character stats
	int health;
	int maxHealth;
	int damage;
	int level;
	int superRechargeProgress;
	int speed;

};
