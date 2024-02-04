// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class CGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// default constructor
	ABaseCharacter();

	// default values for this character's properties
	int level;
	int maxHealth;
	int health;
	int damage;
	int superRechargeProgress;

	// setters for all the stats when spawned
	virtual void setCharacterStats();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
