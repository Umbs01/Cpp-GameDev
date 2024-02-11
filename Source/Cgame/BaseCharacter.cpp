// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacter.h"

///////////////////////////////////////////////////////////////
// ABaseCharacter

ABaseCharacter::ABaseCharacter()
{


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

//////////////////////////////////////////////////////////////////
// Gameplay Mechanics

// Return the player's current health
int ABaseCharacter::GetHealth()
{
	return CurrentHealth;
}

// Return the player's max health
int ABaseCharacter::GetMaxHealth()
{
	return MaxHealth;
}

// Modify the player's health by the specified amount
// -ve values are subtracted +ve are added
void ABaseCharacter::UpdateHealth(int DeltaHealth)
{
	// Check if the player is dead
	if (CurrentHealth >= 0.f) return;

	// Assign the old health value
	int OldValue = CurrentHealth;

	CurrentHealth += DeltaHealth;

	// Make sure that the updated CurrentHealth is in an acceptable range
	// In this case it'll never be less than -1 or more than MaxHealth
	CurrentHealth = FMath::Clamp(CurrentHealth, -1, MaxHealth);

	// Compare the value before we changed it with the new value
	if (CurrentHealth != OldValue)
	{
		OnHealthChanged.Broadcast(OldValue, CurrentHealth, MaxHealth);
	}

	// Check if the player is Dead
	if (CurrentHealth <= 0.f)
	{
		OnPlayerDied.Broadcast();
	}

}

// Restore the player health
void ABaseCharacter::RestoretoFullHealth()
{
	CurrentHealth = MaxHealth;
}

// Set the maximum player's allowable health
void ABaseCharacter::SetMaxHealth(int NewMaxHealth)
{
	// will implement the range checking later
	MaxHealth = NewMaxHealth;
}

// Return the player's current Super Recharge Progress
float ABaseCharacter::GetSuperProgress()
{
	return SuperProgress;
}

// Return the player's recuperation factor
float ABaseCharacter::GetSuperRecuperationFactor()
{
	return SuperRecuperationFactor;
}

// Set the player's recuperation factor
void ABaseCharacter::SetSuperRecuperationFactor(float NewRecupertaionFactor)
{
	// will implement the range checking later
	SuperRecuperationFactor = NewRecupertaionFactor;
}

// Return the player's current charges
float ABaseCharacter::GetCurrentCharges()
{
	return CurrentCharges;
}

// player fire the weapon!
void ABaseCharacter::Blast()
{
	// the cost to fire once is 1.0f
	// check if we have anough charges before allowing the action to work
	if (Charges >= 1.0f)
	{
		// Do the Busting

		// Deduct the charge used
		CurrentCharges -= 1;
	}
}