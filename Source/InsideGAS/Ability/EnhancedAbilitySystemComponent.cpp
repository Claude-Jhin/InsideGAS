// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedAbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

void UEnhancedAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent,
                                                                            FGameplayAbilityInputBinds BindInfo)
{
	Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
}

void UEnhancedAbilitySystemComponent::BindAbilityActivationToInputComponent(
	UEnhancedInputComponent* EnhancedInputComponent, TMap<UInputAction*, TSubclassOf<UGameplayAbility>> InputAbilityMap)
{
	if (ensureMsgf(EnhancedInputComponent,
	               TEXT("Project must use EnhancedInputComponent to support PlayerControlsComponent")))
	{
		for (auto InputAbility : InputAbilityMap)
		{
			FGameplayAbilitySpec* BindingAbility = FindAbilitySpecFromClass(InputAbility.Value);

			if (BindingAbility)
			{
				UInputAction* InputAction = InputAbility.Key;

				// Pressed event
				EnhancedInputComponent->BindAction(
						InputAction, ETriggerEvent::Started, this,
						&UEnhancedAbilitySystemComponent::AbilityLocalInputPressed,
						BindingAbility->InputID);

				// Released event
				EnhancedInputComponent->BindAction(
					InputAction, ETriggerEvent::Completed, this,
					&UEnhancedAbilitySystemComponent::AbilityLocalInputReleased, BindingAbility->InputID);
			}
		}
	}
}
