// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDBB.h"
#include "Components/ProgressBar.h"

// Set value for health bar
void UHUDBB::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar != nullptr)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

// Set value for charges bar
void UHUDBB::SetCharges(float CurrentCharges, float Initial)
{
	if (ChargesBar != nullptr)
	{
		ChargesBar->SetPercent(CurrentCharges / Initial);
	}
}

// Set value for super progress bar
void UHUDBB::SetSuperProgress(float CurrentSuperProgress, float Initial)
{
	if (SuperProgress != nullptr)
	{
		SuperProgress->SetPercent(CurrentSuperProgress / Initial);
	}
}