// Fill out your copyright notice in the Description page of Project Settings.


#include "BRGameMode.h"

ABRGameMode::ABRGameMode()
{
	// set default pawn class to our Blueprinted Basecharacter
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/BP_Barbarian"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}