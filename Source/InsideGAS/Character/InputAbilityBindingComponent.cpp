// Fill out your copyright notice in the Description page of Project Settings.


#include "InputAbilityBindingComponent.h"

#include "InsideGAS/InsideGAS.h"


// Sets default values for this component's properties
UInputAbilityBindingComponent::UInputAbilityBindingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInputAbilityBindingComponent::OnRegister()
{
	Super::OnRegister();
	UE_LOG(LogInsideGAS, Log, TEXT("Regist Component"));

	const UWorld* ThisWorld = GetWorld();
	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (IsValid(PawnOwner) && IsValid(ThisWorld) && ThisWorld->IsGameWorld())
	{
		PawnOwner->ReceiveRestartedDelegate.AddDynamic(this, &UInputAbilityBindingComponent::OnPawnRestarted);
		PawnOwner->ReceiveControllerChangedDelegate.AddDynamic(
			this, &UInputAbilityBindingComponent::OnControllerChanged);

		if (IsValid(PawnOwner->InputComponent))
		{
			OnPawnRestarted(PawnOwner);
		}
	}
}

void UInputAbilityBindingComponent::OnUnregister()
{
	Super::OnUnregister();
	UE_LOG(LogTemp, Log, TEXT("Unregist Component"));
}


void UInputAbilityBindingComponent::OnPawnRestarted(APawn* Pawn)
{

}

void UInputAbilityBindingComponent::OnControllerChanged(APawn* Pawn, AController* OldController,
                                                        AController* NewController)
{
}
