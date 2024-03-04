// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/ProgressBar.h"

void UPlayerHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar != nullptr)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

// Set value for charges bar
void UPlayerHUD::SetCharges(float CurrentCharges, float MaxCharge)
{
	if (ChargesBar != nullptr)
	{
		ChargesBar->SetPercent(CurrentCharges / MaxCharge);
	}
}

// Set value for super progress bar
void UPlayerHUD::SetSuperProgress(float CurrentSuperProgress, float MaxSuper)
{
	if (SuperProgress != nullptr)
	{
		SuperProgress->SetPercent(CurrentSuperProgress / MaxSuper);
	}
}
