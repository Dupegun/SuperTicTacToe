// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacGameStateBase.h"
#include "Engine/World.h"
#include "SuperTicTacGameModeBase.h"
#include "HelpersFuncLib.h"

void ATicTacGameStateBase::HandleNewElementState_Implementation(AGameBoardElementBase* BoardElement, EElementState NewElementState)
{
	LastChangedElement = BoardElement;
	TurnComplete();
}

void ATicTacGameStateBase::StartMatch_Implementation()
{

}

void ATicTacGameStateBase::TurnComplete_Implementation()
{
	CheckWin();
}

void ATicTacGameStateBase::CheckWin()
{
	if (IsValid(GetWorld()))
	{
		auto GameMode = Cast<ASuperTicTacGameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(GameMode))
		{
			if (IsValid(LastChangedElement))
			{
				uint8 NumToWin = GameMode->NumElementsToWin;
				EElementState TargetState = LastChangedElement->ElementState;
				uint8 bIsSuccess = false;
				FIntVector InIndex = GameMode->GetBoardElementIndex(LastChangedElement, bIsSuccess);
				if (bIsSuccess)
				{
					FIntVector FieldSize = GameMode->GameFieldSize;

					uint8 bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, 0, 0));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(0, NumToWin, 0));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(0, 0, NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, NumToWin, 0));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, -NumToWin, 0));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, NumToWin, -NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, NumToWin, NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, -NumToWin, NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, -NumToWin, -NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, 0, NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(NumToWin, 0, -NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(0, NumToWin, NumToWin));
					if (!bWasWin)
						bWasWin = CheckLine(TargetState, InIndex, FIntVector(0, NumToWin, -NumToWin));
					

					if (!bWasWin)
					{
						auto AllElements = GameMode->GetAllElements();
						uint8 EmptyElementsCount = 0;
						for (auto It = AllElements.CreateConstIterator(); It; ++It)
						{
							if (IsValid(*It))
							{
								if ((*It)->ElementState == EElementState::ES_None)
								{
									EmptyElementsCount++;
								}
							}
						}
						if (EmptyElementsCount == 0)
						{
							UE_LOG(LogTemp, Warning, TEXT("Draw!"));
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("Win!"));
					}
				}
			}
		}
	}
}

bool ATicTacGameStateBase::CheckPlane(FIntVector InitialPoint, FIntVector PlaneNormal, EElementState TargetState)
{
	if (IsValid(GetWorld()))
	{
		auto GameMode = Cast<ASuperTicTacGameModeBase>(GetWorld()->GetAuthGameMode());
		if (IsValid(GameMode))
		{
			FIntVector FieldSize = GameMode->GameFieldSize;
			uint8 NumToWin = GameMode->NumElementsToWin;

			//Z is normal for plane
			if (PlaneNormal == FIntVector(0, 0, 1))
			{
				for (int i = 0; i < FieldSize.X; i++)
				{
					uint8 bIsWin = CheckLine(TargetState, FIntVector(i, 0, InitialPoint.Z), FIntVector(i, FieldSize.Y, InitialPoint.Z));
					if (bIsWin)
					{
						return true;
					}
				}
				
				for (int j = 0; j < FieldSize.Y; j++)
				{
					uint8 bIsWin = CheckLine(TargetState, FIntVector(0, j, InitialPoint.Z), FIntVector(FieldSize.X, j, InitialPoint.Z));
					if (bIsWin)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool ATicTacGameStateBase::CheckLine(EElementState TargetState, FIntVector InitialPoint, FIntVector DeltaVector)
{
	if (!IsValid(GetWorld())) { return false; }

	auto GameMode = Cast<ASuperTicTacGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) { return false; }

	FIntVector FieldSize	= GameMode->GameFieldSize;
	uint8 NumToWin			= GameMode->NumElementsToWin;
	uint8 CurrentNum		= 0;

	FIntVector LineStart	= UHelpersFuncLib::ClampVectorComponents(InitialPoint - DeltaVector, FIntVector(0,0,0), FieldSize-FIntVector(1,1,1));
	FIntVector LineEnd		= UHelpersFuncLib::ClampVectorComponents(InitialPoint + DeltaVector, FIntVector(0,0,0), FieldSize-FIntVector(1,1,1));

	FIntVector Direction = LineEnd - LineStart;
	int32 Length = FMath::FloorToInt(Direction.Size());
	FIntVector StepVector = FIntVector(FMath::Sign(Direction.X), FMath::Sign(Direction.Y), FMath::Sign(Direction.Z));//FIntVector(Direction.X / Length, Direction.Y / Length, Direction.Z / Length);
	//UE_LOG(LogTemp, Warning, TEXT("Direction size %f Length %f"), Direction.Size(), Length);
	for (int step = 0; step <= FMath::RoundToInt(Direction.GetMax()); step++)
	{
		auto Element = GameMode->GetBoardElement(LineStart + StepVector*step);
		if (IsValid(Element))
		{
			uint8 StateSuccess = Element->ElementState == TargetState;
			if (StateSuccess)
			{
				CurrentNum++;
				if (CurrentNum == NumToWin)
				{
					return true;
				}
			}
			else
			{
				//CurrentNum = 0;
			}
		}
	}

	return false;

}
