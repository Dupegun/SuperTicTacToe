// Fill out your copyright notice in the Description page of Project Settings.

#include "HelpersFuncLib.h"

FIntVector UHelpersFuncLib::ClampVectorComponents(const FIntVector X, const FIntVector Min, const FIntVector Max)
{
	return FIntVector(FMath::Clamp(X.X, Min.X, Max.X), FMath::Clamp(X.Y, Min.Y, Max.Y), FMath::Clamp(X.Z, Min.Z, Max.Z));
}
