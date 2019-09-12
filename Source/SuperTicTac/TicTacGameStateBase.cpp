// Fill out your copyright notice in the Description page of Project Settings.

#include "TicTacGameStateBase.h"

void ATicTacGameStateBase::HandleNewElementState_Implementation(AGameBoardElementBase* BoardElement, EElementState NewElementState)
{
	TurnComplete();
}

void ATicTacGameStateBase::StartMatch_Implementation()
{

}

void ATicTacGameStateBase::TurnComplete_Implementation()
{
	CurrentTurnPlayerIndex = (CurrentTurnPlayerIndex + 1) % 2;
}
