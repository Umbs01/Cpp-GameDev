// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CGAME_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	/* Update HUD with current health. */
	void SetHealth(float CurrentHealth, float MaxHealth);

	/* Update HUD with current charges. */
	void SetCharges(float CurrentCharges, float Initial);

	/* Update HUD with current super progress. */
	void SetSuperProgress(float CurrentSuperProgress, float Initial);

	/* Widget to use to display current health. */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* HealthBar;

	/* Widget to use to display current charges. */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ChargesBar;

	/* Widget to use to display current super progress. */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* SuperProgress;
};
