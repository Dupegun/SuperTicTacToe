// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SuperTicTacGameModeBase.generated.h"

class AGameBoardBase;

UCLASS()
class SUPERTICTAC_API ASuperTicTacGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	ASuperTicTacGameModeBase();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AGameBoardBase> GameBoardClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GameBoardElementSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntVector GameFieldSize;

	UPROPERTY(BlueprintReadOnly)
	TMap<AGameBoardBase*, uint8> SpawnedGameBoards;

	UFUNCTION(BlueprintCallable)
	void CreateGameField();
};
