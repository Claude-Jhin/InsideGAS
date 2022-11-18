// Fill out your copyright notice in the Description page of Project Settings.


#include "GASCharacterBase.h"
#include "AbilitySystemComponent.h"
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
