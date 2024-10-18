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
	GameMode = EGameMode::GM_AIVsPlayer;
	
	if (GameMode == EGameMode::GM_AIVsPlayer)
	{
		// Initialize AI player
		AIPlayer = NewObject<UAIPlayer>(UAIPlayer::StaticClass());
	}
}


void UTTTGameManager::HandleMove(int32 X, int32 Y)
{
	if (Board[X][Y] == 0)  // If the cell is empty
	{
		Board[X][Y] = CurrentPlayer;  // Set the current player's symbol

		CheckWinCondition();

		// Switch player
		CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;

		// If it's AI's turn, trigger AI move
		if (GameMode == EGameMode::GM_AIVsPlayer && CurrentPlayer == 2)
		{
			if (AIPlayer)
			{
				// Let AI make its move
				FIntPoint Move = AIPlayer->MakeMove(Board);
				if (Move.X != -1 && Move.Y != -1)
				{
					// Find the corresponding block based on the AI's move
					for (ATTTBlock* Block : Blocks)
					{
						if (Block && Block->X == Move.X && Block->Y == Move.Y)
						{
							// Trigger the block's click event
							Board[Move.X][Move.Y] = CurrentPlayer;
							Block->BlockChangeColor(CurrentPlayer);
							break;
						}
					}
				}
			}
			
		}
	}
}

void UTTTGameManager::CheckWinCondition()
{
	// Add win condition check logic here
}