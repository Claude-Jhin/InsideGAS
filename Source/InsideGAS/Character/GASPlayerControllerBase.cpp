// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPlayerControllerBase.h"
#include "AbilitySystemComponent.h"
#include "GASCharacterBase.h"


// Sets default values
AGASPlayerControllerBase::AGASPlayerControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGASPlayerControllerBase::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	AGASCharacterBase* PossessedCharacter = Cast<AGASCharacterBase>(P);

	if (IsValid(PossessedCharacter))
	{
		PossessedCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(PossessedCharacter, PossessedCharacter);
	}
}
