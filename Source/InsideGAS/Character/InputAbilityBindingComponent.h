// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Components/ActorComponent.h"
#include "InputAbilityBindingComponent.generated.h"

UENUM()
enum class EInputVersion:uint8
{
	Old,
	Enhanced,
	Mixed,
};

USTRUCT()
struct FOldAbilityInputBinding
{
	GENERATED_BODY()

	int32 InputID = 0;
	
};

USTRUCT()
struct FEnhancedAbilityInputBinding
{
	GENERATED_BODY()

	int32 InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INSIDEGAS_API UInputAbilityBindingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputAbilityBindingComponent();
	
	virtual void OnRegister() override;

	virtual void OnUnregister() override;

protected:
	
	UFUNCTION()
	void OnPawnRestarted(APawn* Pawn);

	UFUNCTION()
	void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

#pragma region OLD_INPUT

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	EInputVersion InputVersion;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input|OldInput|Ability")
	TMap<uint8, TSubclassOf<UGameplayAbility>> OldInputAbilityMap;

private:
	UPROPERTY(Transient)
	TMap<FName, FEnhancedAbilityInputBinding> OldMappedAbilities;

	UPROPERTY(Transient)
	UInputComponent* OldInput;

#pragma endregion OLD_INPUT

#pragma region ENHANCED_INPUT
// protected:
// 	UPROPERTY(EditDefaultsOnly, Category = "Input|Enhanced Input")
// 	UInputMappingContext* InputMappingContext;
//
// 	UPROPERTY(EditDefaultsOnly, Category = "Input|Enhanced Input")
// 	int InputPriority = 0;
//
// 	UPROPERTY(EditDefaultsOnly, Category = "Input|Enhanced Input|Ability")
// 	TMap<class UInputAction*, TSubclassOf<UGameplayAbility>> EnhancedInputAbilityMap;
//
// private:
// 	UPROPERTY(EditDefaultsOnly, Category = "Input|Enhanced Input|Ability")
// 	TMap<UInputAction*, FAbilityInputBinding> EnhancedMappedAbilities;
//
// 	UPROPERTY(Transient)
// 	class UEnhancedInputComponent* EnhancedInput;
#pragma endregion ENHANCED_INPUT

};
