// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"
#include "AbilitySystemComponent.h"

FName AGASCharacterBase::AbilitySystemComponentName(TEXT("AbilitySystemComponent"));

// Sets default values
AGASCharacterBase::AGASCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		AGASCharacterBase::AbilitySystemComponentName);
}

void AGASCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	SetOwner(NewController);
}
