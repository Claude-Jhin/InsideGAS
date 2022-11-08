// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "InputAction.h"
#include "EnhancedAbilitySystemComponent.generated.h"

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32 InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

UCLASS()
class INSIDEGAS_API UEnhancedAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnhancedAbilitySystemComponent(const FObjectInitializer& ObjectInitializer);

	virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent,
	                                                   FGameplayAbilityInputBinds BindInfo) override;

	void BindAbilityActivationToInputComponent(UEnhancedInputComponent* EnhancedInputComponent,
	                                           TMap<UInputAction*, TSubclassOf<UGameplayAbility>> InputAbilityMap);

	UFUNCTION()
	void OnAbilityBindedInputPressed(UInputAction* InputAction);

	UFUNCTION()
	void OnAbilityBindedInputReleased(UInputAction* InputAction);

	UPROPERTY(Transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;
};
