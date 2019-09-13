// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacGameStateBase.h"
#include "Engine/World.h"
#include "SuperTicTacGameModeBase.h"

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
				EElementState TargetState = LastChangedElement->ElementState;
				uint8 bIsSuccess = false;
				FIntVector ResultIndex = GameMode->GetBoardElementIndex(LastChangedElement, bIsSuccess);
				if (bIsSuccess)
				{
					uint8 bWasWin = CheckPlane(ResultIndex, FIntVector(0,0,1), TargetState);
					if (!bWasWin)
						bWasWin = CheckPlane(ResultIndex, FIntVector(0,1,0), TargetState);
					if (!bWasWin)
						bWasWin = CheckPlane(ResultIndex, FIntVector(1,0,0), TargetState);

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
			FIntVector FieldSize	= GameMode->GameFieldSize;
			uint8 NumToWin			= GameMode->NumElementsToWin;
			uint8 CurrentNumX		= 0;
			uint8 CurrentNumY		= 0;
			uint8 CurrentNumXY0		= 0;
			uint8 CurrentNumXY1		= 0;

			uint8 bUseX = PlaneNormal.X != 1;
			uint8 bUseY = PlaneNormal.Y != 1;
			uint8 bUseZ = PlaneNormal.Z != 1;

			for (auto i = bUseX? InitialPoint.X - NumToWin : 0; i <= bUseX? InitialPoint.X + NumToWin : 0; i++)
			{
				for (auto j = bUseY? InitialPoint.Y - NumToWin : 0; j <= bUseY? InitialPoint.Y + NumToWin : 0; j++)
				{
					for (auto k = bUseZ? InitialPoint.Z - NumToWin : 0; k <= bUseZ? InitialPoint.Z + NumToWin : 0; k++)
					{
						if (i<0 || i>(FieldSize.X - 1) || j<0 || j>(FieldSize.Y - 1) || k<0 || k>(FieldSize.Z-1)) { continue; }

						FIntVector IndexToCheck;
						if (PlaneNormal.Z == 1)
						{
							IndexToCheck = FIntVector(i, j, PlaneNormal.Z);
						}
						else if (PlaneNormal.Y == 1)
						{
							IndexToCheck = FIntVector(i, PlaneNormal.Y, k);
						}
						else if (PlaneNormal.X == 1)
						{
							IndexToCheck = FIntVector(PlaneNormal.X, j, k);
						}

						auto BoardElement = GameMode->GetBoardElement(IndexToCheck);
						if (IsValid(BoardElement))
						{
							uint8 bisEqual = TargetState == BoardElement->ElementState;
							if (bisEqual)
							{
								CurrentNumY++;

								if (IndexToCheck.X == IndexToCheck.Y || IndexToCheck.X == IndexToCheck.Z || IndexToCheck.Y == IndexToCheck.Z)
								{
									CurrentNumXY0++;
								}
								if (IndexToCheck.Z == 1 && i == (FieldSize.Y - 1 - j) ||
									IndexToCheck.Y == 1 && i == (FieldSize.Z - 1 - k) ||
									IndexToCheck.X == 1 && j == (FieldSize.X - 1 - k))
								{
									CurrentNumXY1++;
								}
							}
						}

						if (PlaneNormal.Z == 1)
						{
							IndexToCheck = FIntVector(j, i, PlaneNormal.Z); 
						}
						else if (PlaneNormal.Y == 1)
						{
							IndexToCheck = FIntVector(k, PlaneNormal.Y, i);
						}
						else if (PlaneNormal.X == 1)
						{
							IndexToCheck = FIntVector(PlaneNormal.X, k, j);
						}

						BoardElement = GameMode->GetBoardElement(IndexToCheck);
						if (IsValid(BoardElement))
						{
							uint8 bisEqual = TargetState == BoardElement->ElementState;
							if (bisEqual)
							{
								CurrentNumX++;
							}
						}

						if (CurrentNumX == NumToWin || CurrentNumY == NumToWin || CurrentNumXY0 == NumToWin || CurrentNumXY1 == NumToWin)
						{
							UE_LOG(LogTemp, Warning, TEXT("Win!"));
							return true;
						}
					}
					//if (!bUseZ)
					//{
					//	CurrentNumX = 0;
					//	CurrentNumY = 0;
					//}
				}
				//if (!bUseY)
				//{
				//	CurrentNumX = 0;
				//	CurrentNumY = 0;
				//}
			}
			//if (!bUseY)
			//{
			//	CurrentNumX = 0;
			//	CurrentNumY = 0;
			//}
		}
	}
	return false;
}
