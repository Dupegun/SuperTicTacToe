// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelpersFuncLib.generated.h"

/**
 * 
 */
UCLASS()
class SUPERTICTAC_API UHelpersFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION()
	static FIntVector ClampVectorComponents(const FIntVector X, const FIntVector Min, const FIntVector Max);
};
