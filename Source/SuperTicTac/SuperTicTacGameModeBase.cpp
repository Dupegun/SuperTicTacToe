// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperTicTacGameModeBase.h"
#include "GameBoardBase.h"
#include "Engine/World.h"
#include "TicTacGameStateBase.h"
#include "GameBoardElementBase.h"

ASuperTicTacGameModeBase::ASuperTicTacGameModeBase() :
	GameBoardElementSize(200.f),
	GameFieldSize(3,3,3),
	NumElementsToWin(3),
	bIsBoardsCollapsed(false)
{

}

void ASuperTicTacGameModeBase::CreateGameField()
{
	if (ensure(GetWorld()))
	{
		for (auto It = SpawnedGameBoards.CreateConstIterator(); It; ++It)
		{
			if (IsValid(It->Value))
			{
				auto Board = It->Value;
				SpawnedGameBoards.Remove(It->Key);
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
			bool bSuccess = NewGameBoard->FillBoardWithElements();
			if (bSuccess)
			{
				auto GameState = GetGameState<ATicTacGameStateBase>();
				if (IsValid(GameState))
				{
					auto Elements = NewGameBoard->GetAllElements();
					for (auto It = Elements.CreateConstIterator(); It; ++It)
					{
						(*It)->OnNewElementState.AddDynamic(GameState, &ATicTacGameStateBase::HandleNewElementState);
					}
				}
			}
			SpawnedGameBoards.Add(i, NewGameBoard);
		}

		//UnCollapseBoards();
	}
}

AGameBoardElementBase* ASuperTicTacGameModeBase::GetBoardElement(FIntVector Index) const
{
	auto GameBoard = *(SpawnedGameBoards.Find(Index.Z));
	if (IsValid(GameBoard))
	{
		auto TargetValue = GameBoard->BoardElements.Find(Index);
		if (TargetValue)
		{
			return *TargetValue;
		}
	}
	return nullptr;
}

FIntVector ASuperTicTacGameModeBase::GetBoardElementIndex(class AGameBoardElementBase* BoardElement, uint8 &bIsSuccess) const
{
	for (auto It = SpawnedGameBoards.CreateConstIterator(); It; ++It)
	{
		auto CurrentBoard = It->Value;
		if (IsValid(CurrentBoard))
		{
			auto TargetElementIndex = CurrentBoard->BoardElements.FindKey(BoardElement);
			if (TargetElementIndex)
			{
				bIsSuccess = true;
				return *TargetElementIndex;
			}
		}
	}
	bIsSuccess = false;
	return FIntVector(-1, -1, -1);
}

TArray<AGameBoardElementBase*> ASuperTicTacGameModeBase::GetAllElements() const
{
	TArray<AGameBoardElementBase*> ResutArr;
	for (auto It = SpawnedGameBoards.CreateConstIterator(); It; ++It)
	{
		if (IsValid(It->Value))
		{
			ResutArr.Append(It->Value->GetAllElements());
		}
	}
	
	return ResutArr;
}

void ASuperTicTacGameModeBase::UnCollapseBoards()
{
	if (SpawnedGameBoards.Num() == 3)
	{
		auto ZeroBoard = SpawnedGameBoards.FindRef(0);
		if (IsValid(ZeroBoard))
		{
			ZeroBoard->MoveToTarget(FVector(0, GameFieldSize.Y*GameBoardElementSize, GameBoardElementSize));
		}
		auto SecondBoard = SpawnedGameBoards.FindRef(2);
		if (IsValid(SecondBoard))
		{
			SecondBoard->MoveToTarget(FVector(0, -GameFieldSize.Y*GameBoardElementSize, GameBoardElementSize));
		}

		bIsBoardsCollapsed = false;
	}
}

void ASuperTicTacGameModeBase::CollapseBoards()
{
	if (SpawnedGameBoards.Num() == 3)
	{
		auto ZeroBoard = SpawnedGameBoards.FindRef(0);
		if (IsValid(ZeroBoard))
		{
			ZeroBoard->MoveToTarget(FVector(0, 0, 0));
		}
		auto SecondBoard = SpawnedGameBoards.FindRef(2);
		if (IsValid(SecondBoard))
		{
			SecondBoard->MoveToTarget(FVector(0, 0, GameBoardElementSize*2));
		}

		bIsBoardsCollapsed = true;
	}
}
