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
	SetActorTickInterval(0.5f);
	SetActorTickEnabled(true);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	// calls the Super bla bla bla
	Super::Tick(DeltaTime);

	// There are 2 things that can be restored over time, which are:
	// 1) Charges for firing: max 3
	// 2) Super: will gain after dealing damage to another player OR passively gain (Barbarian)

#pragma region Update Super
	// declare the constant super's gain rate
	float ActualSuperRecuperationFactor = SuperRecuperationFactor;

	if (CurrentSuperProgress != MaxSuperProgress)
	{
		// keep track of the value before it being changed
		const float PreviousProgress = CurrentSuperProgress;

		CurrentSuperProgress = FMath::Clamp(CurrentSuperProgress + SuperRecuperationFactor, 0.0f, MaxSuperProgress);
		OnSuperChanged.Broadcast(PreviousProgress, CurrentSuperProgress, MaxSuperProgress);
	}

	// TODO: check if the player successfully deals damage to other player -> gains set amount of super charge

#pragma endregion
	
#pragma region Update Charges
	
	if (CurrentCharges != Charges)
	{
		// keep track of the value before it being changed
		const float PreviousCharges = CurrentCharges;

		CurrentCharges = FMath::Clamp(CurrentCharges + ChargeRecuperationFactor, 0.0f, Charges);
		OnChargeChanged.Broadcast(PreviousCharges, CurrentCharges, Charges);
	}
#pragma endregion

	// Temporarily display debug information
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Green,
		*(FString::Printf(
			TEXT("Health - Current:%d | Maximum:%d"), CurrentHealth, MaxHealth)));
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Yellow,
		*(FString::Printf(
			TEXT("Super - Current:%f | Maximum:%f"), CurrentSuperProgress, MaxSuperProgress)));
	GEngine->AddOnScreenDebugMessage(-1, 0.2f, FColor::Red,
		*(FString::Printf(
			TEXT("Ammo - Current:%f | Maximum:%f"), CurrentCharges, Charges)));
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
float ABaseCharacter::GetCurrentSuperProgress()
{
	return CurrentSuperProgress;
}

// Return the player's max Super
float ABaseCharacter::GetMaxSuperProgress()
{
	return MaxSuperProgress;
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

// player unleashed their super attack!
void ABaseCharacter::SuperMove()
{
	// The cost to use super is 1000.0f
	// Once used the CurrentSuperProgress depletes
	// Check if we have enough charges before allowing the action to work
	if (CurrentSuperProgress >= MaxSuperProgress)
	{
		// Do the Busting
		// Debugging
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,
			*(FString::Printf(
				TEXT("BIGBOOOM"))));

		// Depletes the meter once used
		CurrentSuperProgress -= MaxSuperProgress;
	}
}

// Return the player's current charges
float ABaseCharacter::GetCurrentCharges()
{
	return CurrentCharges;
}

// player fire the weapon!
void ABaseCharacter::Blast()
{
	// the cost to fire once is 100.0f
	// check if we have anough charges before allowing the action to work
	if (CurrentCharges >= 100.0f)
	{
		// Do the Busting
		// Debugging
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,
			*(FString::Printf(
				TEXT("BOOOM"))));

		// Deduct the charge used
		CurrentCharges -= 100.0f;
	}
}