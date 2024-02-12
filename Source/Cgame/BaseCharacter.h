
#pragma once

#include "CoreMinimal.h"
#include "CgameCharacter.h"
#include "BaseCharacter.generated.h"

// Delegate for when stats based on integers are changed.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIntStatUpdated,
	int32, OldValue,
	int32, NewValue,
	int32, MaxValue);

// Delegate for when the player dies
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerIsDead);

// Delegate for when stats based on floats are changed.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFloatStatUpdated,
	float, OldValue,
	float, NewValue,
	float, MaxValue);

UCLASS()
class CGAME_API ABaseCharacter : public ACgameCharacter
{
	GENERATED_BODY()

private:
	// Ingame Character Propeties
	// Health
	static constexpr int BaseHealth = 3000;
	int	MaxHealth = BaseHealth;
	int CurrentHealth = BaseHealth;

	// Damage
	static constexpr float Damage = 950.0f;
	static constexpr float Charges = 300.0f; // 300 -> 100 per shots for 3 maximum
	float CurrentCharges = Charges;
	float ChargeRecuperationFactor = 0.50f; // Rate at which charges are recharged

	// Super
	static constexpr float BaseSuperProgress = 0.0f;
	static constexpr float MaxSuperProgress = 1000.0f;
	float CurrentSuperProgress = BaseSuperProgress;
	float SuperRecuperationFactor = 1.0f; // Rate at which super is recharged

public:
	// Default Class constructor
	ABaseCharacter();

#pragma region Health

	// Return the player's current health
	UFUNCTION(BlueprintPure, Category = "Player|Health")
	int GetHealth();

	// Return the player's max health
	UFUNCTION(BlueprintPure, Category = "Player|Health")
	int GetMaxHealth();

	// Modify the player's health by the specified amount
	// -ve values are subtracted +ve are added
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void UpdateHealth(int DeltaHealth);

	// Restore the player health
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void RestoretoFullHealth();

	// Set the maximum player's allowable health
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void SetMaxHealth(int NewMaxHealth);

	// Triggered when the player's health is updated.
	UPROPERTY(BlueprintAssignable, Category = "Player|Health")
	FIntStatUpdated OnHealthChanged;

	// Triggered when the player dies.
	UPROPERTY(BlueprintAssignable, Category = "Player|Health")
	FPlayerIsDead OnPlayerDied;

#pragma endregion

#pragma region Super

	// Return the player's current Super Recharge Progress
	UFUNCTION(BlueprintPure, Category = "Player|Super")
	float GetCurrentSuperProgress();

	// Return the player's max Super Progress
	UFUNCTION(BlueprintPure, Category = "Player|Super")
	float GetMaxSuperProgress();

	// Return the player's recuperation factor
	UFUNCTION(BlueprintPure, Category = "Player|Super")
	float GetSuperRecuperationFactor();

	// Set the player's recuperation factor
	UFUNCTION(BlueprintCallable, Category = "Player|Super")
	void SetSuperRecuperationFactor(float NewRecupertaionFactor);

	// player unleashed their super attack!
	UFUNCTION(BlueprintCallable, Category = "Player|Super")
	void SuperMove();

	// Triggered when the player's stamina is updated.
	UPROPERTY(BlueprintAssignable, Category = "Player|Super")
	FFloatStatUpdated OnSuperChanged;

#pragma endregion

#pragma region Damage

	// Return the player's current charges
	UFUNCTION(BlueprintPure, Category = "Player|Damage")
	float GetCurrentCharges();

	// player fire the weapon!
	UFUNCTION(BlueprintCallable, Category = "Player|Damage")
	void Blast();

	// Triggered when the players charges is updated.
	UPROPERTY(BlueprintAssignable, Category = "Player|Damage")
	FFloatStatUpdated OnChargeChanged;

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
