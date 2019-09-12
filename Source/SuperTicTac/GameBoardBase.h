// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameBoardBase.generated.h"

class AGameBoardElementBase;

UCLASS()
class SUPERTICTAC_API AGameBoardBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameBoardBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 BoardLengthX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 BoardLengthY;

	UPROPERTY(BlueprintReadOnly)
	uint8 BoardIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AGameBoardElementBase> BoardElementClass;

	UPROPERTY(EditAnywhere)
	float BoardElementSize;

	UPROPERTY(BlueprintReadOnly)
	TMap<AGameBoardElementBase* , FIntVector> BoardElements;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void FillBoardWithElements();

};
