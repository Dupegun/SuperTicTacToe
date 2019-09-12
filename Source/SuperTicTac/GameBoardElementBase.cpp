// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBoardElementBase.h"

// Sets default values
AGameBoardElementBase::AGameBoardElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameBoardElementBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameBoardElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameBoardElementBase::SetNewElementState(EElementState NewState)
{
	if (NewState != ElementState)
	{
		ElementState = NewState;
		OnNewElementState.Broadcast(this, ElementState);
	}
}

