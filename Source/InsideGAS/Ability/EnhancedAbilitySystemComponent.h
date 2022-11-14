// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EnhancedAbilitySystemComponent.generated.h"

UCLASS()
class INSIDEGAS_API UEnhancedAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent,
	                                                   FGameplayAbilityInputBinds BindInfo) override;
	
	void BindAbilityActivationToInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	                                           TMap<class UInputAction*, TSubclassOf<UGameplayAbility>> InputAbilityMap);
};
