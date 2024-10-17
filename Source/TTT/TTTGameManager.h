// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TTTGameManager.generated.h"

/**
 * 
 */
UCLASS()
class TTT_API UTTTGameManager : public UObject
{
	GENERATED_BODY()
	
	UTTTGameManager();
public:
	
	TArray<TArray<int32>> Board;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	int32 CurrentPlayer;  
	
	void HandleMove(int32 X, int32 Y);

	// Function to check win conditions
	void CheckWinCondition();
};
