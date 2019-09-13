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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 NumElementsToWin;

	UPROPERTY(BlueprintReadOnly)
	TMap<uint8, AGameBoardBase*> SpawnedGameBoards;

	UFUNCTION(BlueprintCallable)
	void CreateGameField();

	UFUNCTION(BlueprintCallable)
	class AGameBoardElementBase* GetBoardElement(FIntVector Index) const;
	UFUNCTION(BlueprintCallable)
	FIntVector GetBoardElementIndex(class AGameBoardElementBase* BoardElement, uint8 &bIsSuccess) const;
	UFUNCTION(BlueprintCallable)
	TArray<AGameBoardElementBase*> GetAllElements() const;
};
