// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTGameManager.h"

UTTTGameManager::UTTTGameManager()
{
	// Initialize the board with zeros (empty cells)
	Board.SetNum(3);
	for (int32 i = 0; i < 3; ++i)
	{
		Board[i].SetNum(3);
		for (int32 j = 0; j < 3; ++j)
		{
			Board[i][j] = 0;  // All cells are empty at the start
		}
	}

	CurrentPlayer = 1;  // X starts the game
}

void UTTTGameManager::HandleMove(int32 X, int32 Y)
{
	if (Board[X][Y] == 0)
	{
		Board[X][Y] = CurrentPlayer;
		CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;  // Switch player
		CheckWinCondition();
	}
}

void UTTTGameManager::CheckWinCondition()
{
	// Check for win conditions
	// (You can add logic here to check rows, columns, and diagonals)
}