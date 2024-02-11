
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

private:
	// Ingame Character Propeties
	// Health
	static constexpr int BaseHealth = 3000;
	int	MaxHealth = BaseHealth;
	int CurrentHealth = BaseHealth;

	// Damage
	static constexpr float Damage = 950.0f;
	static constexpr float Charges = 3.0f;
	float CurrentCharges = Charges;
	float DamageRecuperationFactor = 1.0f; // Rate at which charges are recharged

	// Super
	static constexpr float BaseSuperProgress = 0.0f;
	float SuperProgress = BaseSuperProgress;
	float SuperRecuperationFactor = 1.0f; // Rate at which super is recharged

public:
	// Default Class constructor
	ABaseCharacter();

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

	// Return the player's current Super Recharge Progress
	UFUNCTION(BlueprintPure, Category = "Player|Super")
	float GetSuperProgress();

	// Return the player's recuperation factor
	UFUNCTION(BlueprintPure, Category = "Player|Super")
	float GetSuperRecuperationFactor();

	// Set the player's recuperation factor
	UFUNCTION(BlueprintCallable, Category = "Player|Super")
	void SetSuperRecuperationFactor(float NewRecupertaionFactor);

	// Return the player's current charges
	UFUNCTION(BlueprintPure, Category = "Player|Damage")
	float GetCurrentCharges();

	// player fire the weapon!
	UFUNCTION(BlueprintCallable, Category = "Player|Damage")
	void Blast();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
