// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UGASAttributeSet::UGASAttributeSet()
{
}

void UGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	if (Attribute == GetMaxHealthAttribute() && IsValid(AbilitySystemComponent))
	// GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		const float CurrentMaxHealth = MaxHealth.GetCurrentValue();
		if (!FMath::IsNearlyEqual(CurrentMaxHealth, NewValue))
		{
			const float CurrentHealth = Health.GetCurrentValue();
			float HealthDelta = CurrentMaxHealth > 0.0f ? CurrentHealth * NewValue / CurrentMaxHealth  - CurrentHealth : NewValue;
			AbilitySystemComponent->ApplyModToAttributeUnsafe(GetHealthAttribute(), EGameplayModOp::Additive, HealthDelta);
		}
	}
}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	} 
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldHealth);
}

void UGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxHealth, OldMaxHealth);
}

void UGASAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, HealthRegenRate, OldHealthRegenRate);
}
