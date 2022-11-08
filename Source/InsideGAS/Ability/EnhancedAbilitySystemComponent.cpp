// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedAbilitySystemComponent.h"
#include "EnhancedInputComponent.h"

namespace AbilityInputBindingComponent_Impl
{
	constexpr int32 InvalidInputID = 10;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
	}
}

UEnhancedAbilitySystemComponent::UEnhancedAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

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
		for (auto& InputBinding : MappedAbilities)
		{
			const int32 NewInputID = AbilityInputBindingComponent_Impl::GetNextInputID();
			InputBinding.Value.InputID = NewInputID;

			for (FGameplayAbilitySpecHandle AbilityHandle : InputBinding.Value.BoundAbilitiesStack)
			{
				FGameplayAbilitySpec* FoundAbility = FindAbilitySpecFromHandle(AbilityHandle);
				if (FoundAbility != nullptr)
				{
					FoundAbility->InputID = NewInputID;
				}
			}
		}
		
		for (auto InputAbility : InputAbilityMap)
		{
			FGameplayAbilitySpec AbilitySpec = BuildAbilitySpecFromClass(InputAbility.Value);

			if (IsValid(AbilitySpec.Ability))
			{
				FGameplayAbilitySpecHandle AbilitySpecHandle = GiveAbility(AbilitySpec);
				
				using namespace AbilityInputBindingComponent_Impl;

				FGameplayAbilitySpec* BindingAbility = FindAbilitySpecFromHandle(AbilitySpecHandle);

				UInputAction* InputAction = InputAbility.Key;

				FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
				
				if (AbilityInputBinding)
				{
					FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpecFromHandle(AbilityInputBinding->BoundAbilitiesStack.Top());
					if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
					{
						OldBoundAbility->InputID = InvalidInputID;
					}
				}
				else
				{
					AbilityInputBinding = &MappedAbilities.Add(InputAction);
					AbilityInputBinding->InputID = GetNextInputID();
				}

				if (BindingAbility)
				{
					BindingAbility->InputID = AbilityInputBinding->InputID;
				}

				AbilityInputBinding->BoundAbilitiesStack.Push(AbilitySpecHandle);

				// Pressed event
				if (AbilityInputBinding->OnPressedHandle == 0)
				{
					AbilityInputBinding->OnPressedHandle = EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UEnhancedAbilitySystemComponent::OnAbilityBindedInputPressed, InputAction).GetHandle();
				}

				// Released event
				if (AbilityInputBinding->OnReleasedHandle == 0)
				{
					AbilityInputBinding->OnReleasedHandle = EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UEnhancedAbilitySystemComponent::OnAbilityBindedInputReleased, InputAction).GetHandle();
				}
			}
		}
	}
}

void UEnhancedAbilitySystemComponent::OnAbilityBindedInputPressed(UInputAction* InputAction)
{
	using namespace AbilityInputBindingComponent_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputPressed(FoundBinding->InputID);
	}
}

void UEnhancedAbilitySystemComponent::OnAbilityBindedInputReleased(UInputAction* InputAction)
{
	using namespace AbilityInputBindingComponent_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputReleased(FoundBinding->InputID);
	}
}
