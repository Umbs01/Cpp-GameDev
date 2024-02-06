// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

//////////////////////////////////////////////////////////
// ABaseCharacter

ABaseCharacter::ABaseCharacter()
{
	setCharacterStats();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using BaseCharacter."));

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// setters for ingame character stats
void ABaseCharacter::setCharacterStats()
{
	maxHealth = 3000;
	health = maxHealth;
	damage = 950;
	level = 1;
	speed = 50;
	superRechargeProgress = 0;
}