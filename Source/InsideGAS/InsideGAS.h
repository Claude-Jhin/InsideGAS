// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

INSIDEGAS_API DECLARE_LOG_CATEGORY_EXTERN(LogInsideGAS, All, All);

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	// 0 None
	None			UMETA(DisplayName = "None"),

	// 1 Jump
	Jump			UMETA(DisplayName = "Jump"),
	
	// 2 T
	OldTestInput		UMETA(DisplayName = "OldTestInput"),
};
