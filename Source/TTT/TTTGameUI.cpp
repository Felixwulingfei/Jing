// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTGameUI.h"

void UTTTGameUI::UpdateModeText(FString ModeTextValue)
{
	if (ModeText)
	{
		ModeText->SetText(FText::FromString(ModeTextValue));
	}
}

void UTTTGameUI::UpdateDifficultyText(FString DifficultyTextValue)
{
	if (DifficultyText)
	{
		DifficultyText->SetText(FText::FromString(DifficultyTextValue));
	}
}

void UTTTGameUI::UpdateTurnText(FString TurnTextValue)
{
	if (TurnText)
	{
		TurnText->SetText(FText::FromString(TurnTextValue));
	}
}