// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

//////////////////////////////////////////////////////////
// ABaseCharacter

ABaseCharacter::ABaseCharacter()
{
	setCharacterStats();
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