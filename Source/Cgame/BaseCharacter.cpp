// Fill out your copyright notice in the Description page of Project Settings.
// n word

#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// adjust the camera to the model's height
	Super::BaseEyeHeight = 20;

	// setting up the character's stats when spawned
	setCharacterStats();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::setCharacterStats()
{

	level = 1;
	maxHealth = 3000;
	health = maxHealth;
	damage = 950;
	superRechargeProgress = 0;

}