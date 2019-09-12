// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTicTacGameModeBase.h"
#include "GameBoardBase.h"
#include "Engine/World.h"

ASuperTicTacGameModeBase::ASuperTicTacGameModeBase() :
	GameBoardElementSize(200.f),
	GameFieldSize(3,3,3)
{

}

void ASuperTicTacGameModeBase::CreateGameField()
{
	if (ensure(GetWorld()))
	{
		for (auto It = SpawnedGameBoards.CreateConstIterator(); It; ++It)
		{
			if (IsValid((*It).Key))
			{
				auto Board = (*It).Key;
				SpawnedGameBoards.Remove((*It).Key);
				if (IsValid(Board))
				{
					Board->Destroy();
				}
				//(*It).Key->Destroy();
			}
		}

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		for (int i = 0; i < GameFieldSize.Z; i++)
		{
			FTransform SpawnTransform(FVector(0.f, 0.f, i*GameBoardElementSize));
			auto NewGameBoard				= GetWorld()->SpawnActor<AGameBoardBase>(GameBoardClass, SpawnTransform, SpawnParams);
			NewGameBoard->BoardElementSize	= GameBoardElementSize;
			NewGameBoard->BoardIndex		= i;
			NewGameBoard->FillBoardWithElements();
			SpawnedGameBoards.Add(NewGameBoard, i);
		}
	}
}
