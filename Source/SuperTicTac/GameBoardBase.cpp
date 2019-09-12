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
	
	FillBoardWithElements();

}

// Called every frame
void AGameBoardBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGameBoardBase::FillBoardWithElements()
{
	if (ensure(GetWorld()))
	{
		for (auto It = BoardElements.CreateConstIterator(); It; ++It)
		{
			if (IsValid((*It).Key))
			{
				auto Element = (*It).Key;
				BoardElements.Remove((*It).Key);
				if (IsValid(Element))
				{
					Element->Destroy();
				}
			}
		}

		FVector StartCalcLoc = GetActorLocation() - FVector(BoardLengthX, BoardLengthY, 0.f)*BoardElementSize/2;
		for (int i = 0; i < BoardLengthX; i++)
		{
			for (int j = 0; j < BoardLengthY; j++)
			{
				FTransform SpawnTransform(StartCalcLoc + FVector(i+0.5f, j+0.5f, 0.f)*BoardElementSize);
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				auto SpawnedElement = GetWorld()->SpawnActor<AGameBoardElementBase>(BoardElementClass, SpawnTransform, SpawnParams);
				SpawnedElement->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
				BoardElements.Add(SpawnedElement, FIntVector(i, j, BoardIndex));
			}
		}
		return true;
	}
	return false;
}

TArray<AGameBoardElementBase*> AGameBoardBase::GetAllElements() const
{
	TArray<AGameBoardElementBase*> BoardElementsKeys;
	BoardElements.GenerateKeyArray(BoardElementsKeys);
	return BoardElementsKeys;
}

