// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayer.h"

FIntPoint UAIPlayer::MakeMove(const TArray<TArray<int32>>& Board)
{
	if (AILevel == EDifficultyLevel::DL_Hard)
	{
		FIntPoint WinningMove = FindWinningMove(Board, 2);
        if (WinningMove.X != -1 && WinningMove.Y != -1)
        {
        	return WinningMove; 
        }
    
        FIntPoint BlockingMove = FindBlockingMove(Board, 1);
        if (BlockingMove.X != -1 && BlockingMove.Y != -1)
        {
        	return BlockingMove; 
        }
	}
	
	
	return MakeRandomMove(Board);
}

FIntPoint UAIPlayer::MakeRandomMove(const TArray<TArray<int32>>& Board)
{
	TArray<FIntPoint> AvailableMoves;

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

	if (AvailableMoves.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, AvailableMoves.Num() - 1);
		return AvailableMoves[RandomIndex];
	}

	return FIntPoint(-1, -1);
}

FIntPoint UAIPlayer::FindWinningMove(const TArray<TArray<int32>>& Board, int32 Player)
{
	for (int32 i = 0; i < 3; i++)
	{
		if (Board[i][0] == Player && Board[i][1] == Player && Board[i][2] == 0)
			return FIntPoint(i, 2);
		if (Board[i][0] == Player && Board[i][2] == Player && Board[i][1] == 0)
			return FIntPoint(i, 1);
		if (Board[i][1] == Player && Board[i][2] == Player && Board[i][0] == 0)
			return FIntPoint(i, 0);
	}

	for (int32 i = 0; i < 3; i++)
	{
		if (Board[0][i] == Player && Board[1][i] == Player && Board[2][i] == 0)
			return FIntPoint(2, i);
		if (Board[0][i] == Player && Board[2][i] == Player && Board[1][i] == 0)
			return FIntPoint(1, i);
		if (Board[1][i] == Player && Board[2][i] == Player && Board[0][i] == 0)
			return FIntPoint(0, i);
	}

	if (Board[0][0] == Player && Board[1][1] == Player && Board[2][2] == 0)
		return FIntPoint(2, 2);
	if (Board[0][0] == Player && Board[2][2] == Player && Board[1][1] == 0)
		return FIntPoint(1, 1);
	if (Board[1][1] == Player && Board[2][2] == Player && Board[0][0] == 0)
		return FIntPoint(0, 0);

	if (Board[0][2] == Player && Board[1][1] == Player && Board[2][0] == 0)
		return FIntPoint(2, 0);
	if (Board[0][2] == Player && Board[2][0] == Player && Board[1][1] == 0)
		return FIntPoint(1, 1);
	if (Board[1][1] == Player && Board[2][0] == Player && Board[0][2] == 0)
		return FIntPoint(0, 2);

	return FIntPoint(-1, -1);
}

FIntPoint UAIPlayer::FindBlockingMove(const TArray<TArray<int32>>& Board, int32 Player)
{
	// The logic for blocking is the same as checking for a winning move
	return FindWinningMove(Board, Player);
}