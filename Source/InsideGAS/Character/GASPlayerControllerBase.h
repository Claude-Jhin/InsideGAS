// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GASPlayerControllerBase.generated.h"

UCLASS()
class INSIDEGAS_API AGASPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGASPlayerControllerBase();

	virtual void AcknowledgePossession(APawn* P) override;
};
