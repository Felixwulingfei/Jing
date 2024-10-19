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


		// If it's AI's turn, trigger AI move
		if (GameMode == EGameMode::GM_AIVsPlayer)
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
							Board[Move.X][Move.Y] = 2;
							Block->BlockChangeColor(2);
							break;
						}
					}
				}
			}
			
		}
		else
		{
			CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;
		}
		
		CheckWinCondition(X,Y);
	}
}

void UTTTGameManager::CheckWinCondition(int32 X, int32 Y)
{
	int32 Player = Board[X][Y];

	if (Board[X][0] == Player && Board[X][1] == Player && Board[X][2] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins : row %d"), Player, X);
		return;
	}

	if (Board[0][Y] == Player && Board[1][Y] == Player && Board[2][Y] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins : column %d"), Player, Y);
		return;
	}

	if (X == Y && Board[0][0] == Player && Board[1][1] == Player && Board[2][2] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins"), Player);
		return;
	}

	if (X + Y == 2 && Board[0][2] == Player && Board[1][1] == Player && Board[2][0] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins"), Player);
		return;
	}

	bool bBoardFull = true;
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			if (Board[i][j] == 0)  // at least one empty cell
			{
				bBoardFull = false;
				break;
			}
		}
	}

	if (bBoardFull)
	{
		UE_LOG(LogTemp, Warning, TEXT("The game is a draw"));
	}
}