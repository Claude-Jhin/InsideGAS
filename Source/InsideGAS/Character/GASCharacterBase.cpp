﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GASPlayerControllerBase.h"
#include "InsideGAS/Ability/GASAttributeSet.h"

FName AGASCharacterBase::AbilitySystemComponentName(TEXT("AbilitySystemComponent"));

// Sets default values
AGASCharacterBase::AGASCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		AGASCharacterBase::AbilitySystemComponentName);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSet"));
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

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(
			this, &AGASCharacterBase::OnHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).
		                        AddUObject(this, &AGASCharacterBase::OnMaxHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthRegenRateAttribute()).
		                        AddUObject(this, &AGASCharacterBase::OnHealthRegenRateChanged);
	}

	SetOwner(NewController);
}

void AGASCharacterBase::OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	UE_LOG(LogInsideGAS, Log, TEXT("Try change Health"));
}


void AGASCharacterBase::OnMaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
}

void AGASCharacterBase::OnHealthRegenRateChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
}

float AGASCharacterBase::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float AGASCharacterBase::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AGASCharacterBase::GetHealthRegenRate() const
{
	return AttributeSet->GetHealthRegenRate();
}
