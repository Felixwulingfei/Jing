// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TTTGameUI.generated.h"

/**
 * 
 */
UCLASS()
class TTT_API UTTTGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void UpdateModeText(FString ModeText);

	UFUNCTION(BlueprintCallable, Category="UI")
	void UpdateDifficultyText(FString DifficultyText);

	UFUNCTION(BlueprintCallable, Category="UI")
	void UpdateTurnText(FString TurnText);

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ModeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DifficultyText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TurnText;
};
