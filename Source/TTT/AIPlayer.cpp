// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayer.h"

FIntPoint UAIPlayer::MakeMove(const TArray<TArray<int32>>& Board)
{
	// For now, the AI will simply make a random move
	return MakeRandomMove(Board);
}

FIntPoint UAIPlayer::MakeRandomMove(const TArray<TArray<int32>>& Board)
{
	TArray<FIntPoint> AvailableMoves;

	// Collect all available moves
	for (int32 X = 0; X < 3; X++)
	{
		for (int32 Y = 0; Y < 3; Y++)
		{
			if (Board[X][Y] == 0)
			{
				AvailableMoves.Add(FIntPoint(X, Y));
			}
		}
	}

	// If there are available moves, make a random move
	if (AvailableMoves.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, AvailableMoves.Num() - 1);
		return AvailableMoves[RandomIndex];
	}

	// Return an invalid move if no available moves
	return FIntPoint(-1, -1);
}