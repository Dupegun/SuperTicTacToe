// Fill out your copyright notice in the Description page of Project Settings.

#include "GameBoardBase.h"
#include "GameBoardElementBase.h"
#include "Engine/World.h"

// Sets default values
AGameBoardBase::AGameBoardBase() :
	BoardLengthX(3),
	BoardLengthY(3),
	BoardIndex(0),
	BoardElementClass(AGameBoardElementBase::StaticClass()),
	BoardElementSize(100.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AGameBoardBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameBoardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameBoardBase::FillBoardWithElements()
{
	if (IsValid(GetWorld()))
	{
		FVector StartCalcLoc = GetActorLocation() - FVector(BoardLengthX / 2.f, BoardLengthY / 2.f, 0.f)*BoardElementSize;
		for (int i = 0; i < BoardLengthX; i++)
			for (int j = 0; j < BoardLengthY; j++)
			{
				FTransform SpawnTransform(StartCalcLoc + FVector(i*BoardLengthX, j*BoardLengthY, 0.f));
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				auto SpawnedElement = GetWorld()->SpawnActor<AGameBoardElementBase>(BoardElementClass, SpawnTransform, SpawnParams);
				BoardElements.Add(SpawnedElement, FIntVector(i, j, BoardIndex));
			}
	}
	}
}

