
#pragma once

#include "CoreMinimal.h"
#include "CgameCharacter.h"
#include "BaseCharacter.generated.h"

// Delegate for when stats based on integers are changed.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIntStatUpdated,
	float, OldValue,
	float, NewValue,
	float, MaxValue);

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
	static constexpr float BaseHealth = 3000.f;
	float	MaxHealth = BaseHealth;

	// Damage
	static constexpr float Damage = 950.0f;
	static constexpr float Charges = 300.0f; // 300 -> 100 per shots for 3 maximum
	float CurrentCharges = Charges;
	float ChargeRecuperationFactor = 20.f; // Rate at which charges are recharged

	// Super
	static constexpr float BaseSuperProgress = 0.0f;
	static constexpr float MaxSuperProgress = 1000.0f;
	float CurrentSuperProgress = BaseSuperProgress;
	float SuperRecuperationFactor = 5.0f; // Rate at which super is recharged

public:
	// Default Class constructor
	ABaseCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region Health

	// Return the player's current health
	UFUNCTION(BlueprintPure, Category = "Player|Health")
	float GetCurrentHealth();

	// Setter for Current Health. Clamps the value between 0 and MaxHealth and calls OnHealthUpdate. Should only be called on the server.
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void SetCurrentHealth(float healthValue);

	// Return the player's max health
	UFUNCTION(BlueprintPure, Category = "Player|Health")
	float GetMaxHealth();

	// Modify the player's health by the specified amount
	// -ve values are subtracted +ve are added
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void UpdateHealth(float DeltaHealth);

	// Restore the player health
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void RestoretoFullHealth();

	// Set the maximum player's allowable health
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void SetMaxHealth(float NewMaxHealth);

	/** Event for taking damage. Overridden from APawn.*/
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Triggered when the player's health is updated.
	UPROPERTY(BlueprintAssignable, Category = "Player|Health")
	FIntStatUpdated OnHealthChanged;

	// Triggered when the player dies.
	UPROPERTY(BlueprintAssignable, Category = "Player|Health")
	FPlayerIsDead OnPlayerDied;
	
	// replicating function
	UFUNCTION(BlueprintCallable, Category = "Player|Health")
	void OnHealthUpdate();

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

	// replicate current player health and can be replicated using OnHealthUpdate() function
	UPROPERTY(ReplicatedUsing = OnHealthUpdate)
	float CurrentHealth = BaseHealth;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
