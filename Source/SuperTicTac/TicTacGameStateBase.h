// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameBoardElementBase.h"
#include "TicTacGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchEnd, EElementState, MatchResult);

UCLASS()
class SUPERTICTAC_API ATicTacGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AGameBoardElementBase* LastChangedElement;

	UPROPERTY(BlueprintAssignable)
	FOnMatchEnd OnMatchEnd;
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartMatch();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TurnComplete();

	UFUNCTION(BlueprintNativeEvent)
	void HandleNewElementState(AGameBoardElementBase* BoardElement, EElementState NewElementState);

	UFUNCTION()
	void CheckWin();

	UFUNCTION()
	bool CheckLine(EElementState TargetState, FIntVector InitialPoint, FIntVector DeltaVector);

	UFUNCTION(BlueprintCallable)
	bool GetIsBoardsCollapsed() const;
};
