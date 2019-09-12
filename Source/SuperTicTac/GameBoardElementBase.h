// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoardElementBase.generated.h"

UENUM(BlueprintType)
enum class EElementState : uint8
{
	ES_None		UMETA(DisplayName = "None"),
	ES_Cross	UMETA(DisplayName = "Cross"),
	ES_Zero		UMETA(DisplayName = "Zero")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNewElementState, AGameBoardElementBase*, Element, EElementState, NewState);

UCLASS()
class SUPERTICTAC_API AGameBoardElementBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBoardElementBase();

	UPROPERTY(BlueprintReadOnly)
	EElementState ElementState;

	UPROPERTY(BlueprintAssignable)
	FOnNewElementState OnNewElementState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetNewElementState(EElementState NewState);
};
