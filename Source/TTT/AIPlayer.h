// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIPlayer.generated.h"
class TTTGameManager;

UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	DL_Easy UMETA(DisplayName = "Easy"),
	DL_Hard UMETA(DisplayName = "Hard")
};

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
	
	EDifficultyLevel AILevel;

private:
	FIntPoint MakeRandomMove(const TArray<TArray<int32>>& Board);

	// Find Winning
	FIntPoint FindWinningMove(const TArray<TArray<int32>>& Board, int32 Player);

	// Find Blocking
	FIntPoint FindBlockingMove(const TArray<TArray<int32>>& Board, int32 Player);

};
