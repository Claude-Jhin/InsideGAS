// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "InsideGAS/InsideGAS.h"
#include "InsideGAS/Ability/EnhancedAbilitySystemComponent.h"
#include "InsideGAS/Ability/GASAttributeSet.h"
#include "GASCharacterBase.generated.h"

UCLASS()
class INSIDEGAS_API AGASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASCharacterBase(const FObjectInitializer& ObjectInitializer);
	
	virtual void PossessedBy(AController* NewController) override;
public:
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

protected:

	void OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnMaxHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);
	void OnHealthRegenRateChanged(const FOnAttributeChangeData& OnAttributeChangeData);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	static FName AbilitySystemComponentName;

	UPROPERTY()
	UGASAttributeSet* AttributeSet;

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|Attributes")
	float GetHealthRegenRate() const;
};

