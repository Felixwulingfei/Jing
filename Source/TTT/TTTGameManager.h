// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPlayer.h"
#include "TTTBlock.h"
#include "UObject/NoExportTypes.h"
#include "TTTGameManager.generated.h"

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	GM_AIVsPlayer UMETA(DisplayName = "AI vs Player"),
	GM_LocalPlayerVsPlayer UMETA(DisplayName = "Local Player vs Player")
};
UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	DL_Easy UMETA(DisplayName = "Easy"),
	DL_Hard UMETA(DisplayName = "Hard")
};

UCLASS()
class TTT_API UTTTGameManager : public UObject
{
	GENERATED_BODY()
	
	UTTTGameManager();
public:
	
	TArray<TArray<int32>> Board;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	int32 CurrentPlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	EGameMode GameMode;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	EDifficultyLevel DifficultyLevel;
	
	void HandleMove(int32 X, int32 Y);

	// Function to check win conditions
	void CheckWinCondition(int32 X, int32 Y);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	UAIPlayer* AIPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	TArray<ATTTBlock*> Blocks;
};
