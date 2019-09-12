// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameBoardElementBase.h"
#include "TicTacGameStateBase.generated.h"


UCLASS()
class SUPERTICTAC_API ATicTacGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(BlueprintReadWrite)
	uint8 CurrentTurnPlayerIndex;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartMatch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TurnComplete();

	UFUNCTION(BlueprintNativeEvent)
	void HandleNewElementState(AGameBoardElementBase* BoardElement, EElementState NewElementState);
};
