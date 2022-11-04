// Copyright Epic Games, Inc. All Rights Reserved.

#include "InsideGASGameMode.h"
#include "InsideGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInsideGASGameMode::AInsideGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
