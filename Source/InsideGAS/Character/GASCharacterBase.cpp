// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"
#include "AbilitySystemComponent.h"

FName AGASCharacterBase::AbilitySystemComponentName(TEXT("AbilitySystemComponent"));

// Sets default values
AGASCharacterBase::AGASCharacterBase(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
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

		if (GetLocalRole() == ROLE_Authority)
		{
			for (TTuple<EGASAbilityInputID, TSubclassOf<UGameplayAbility>>& Ability : OldInputDefaultAbilities)
			{
				AbilitySystemComponent->GiveAbility(
					FGameplayAbilitySpec(Ability.Value, 1, static_cast<int32>(Ability.Key), this));
			}
		}
	}

	SetOwner(NewController);
}
