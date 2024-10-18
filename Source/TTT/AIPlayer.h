// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TTT_API UAIPlayer : public UObject
{
	GENERATED_BODY()
public:
	// Function to make a move
	FIntPoint MakeMove(const TArray<TArray<int32>>& Board);

private:
	FIntPoint MakeRandomMove(const TArray<TArray<int32>>& Board);
};
