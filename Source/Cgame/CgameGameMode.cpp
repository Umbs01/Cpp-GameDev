// Copyright Epic Games, Inc. All Rights Reserved.

#include "CgameGameMode.h"
#include "CgameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACgameGameMode::ACgameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
