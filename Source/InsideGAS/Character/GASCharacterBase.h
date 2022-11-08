// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "InsideGAS/InsideGAS.h"
#include "InsideGAS/Ability/EnhancedAbilitySystemComponent.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UAbilitySystemComponent* AbilitySystemComponent;

	static FName AbilitySystemComponentName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Binding")
	TMap<EGASAbilityInputID, TSubclassOf<UGameplayAbility>> OldInputDefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS|Binding")
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> EnhancedInputDefaultAbilities;
};
