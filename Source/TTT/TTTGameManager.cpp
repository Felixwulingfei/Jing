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
		AIPlayer = NewObject<UAIPlayer>(UAIPlayer::StaticClass());
	}
}


void UTTTGameManager::HandleMove(int32 X, int32 Y)
{
	if (Board[X][Y] == 0)
	{
		Board[X][Y] = CurrentPlayer;
		CheckWinCondition(X, Y);

		if (bIsGameEnd == 1)
		{
			return;  // 如果玩家获胜，不执行后续的AI操作
		}
		
		if (GameMode == EGameMode::GM_AIVsPlayer)
		{
			if (AIPlayer)
			{
				AIPlayer->AILevel = DifficultyLevel;
				FIntPoint Move = AIPlayer->MakeMove(Board);
				if (Move.X != -1 && Move.Y != -1)
				{
					for (ATTTBlock* Block : Blocks)
					{
						if (Block && Block->X == Move.X && Block->Y == Move.Y)
						{
							Board[Move.X][Move.Y] = 2;
							Block->BlockChangeColor(2);
						}
					}
					CheckWinCondition(Move.X, Move.Y);
				}
			}
			
		}
		else
		{
			CurrentPlayer = (CurrentPlayer == 1) ? 2 : 1;
		}
	}
}

void UTTTGameManager::CheckWinCondition(int32 X, int32 Y)
{
	int32 Player = Board[X][Y];

	if (Board[X][0] == Player && Board[X][1] == Player && Board[X][2] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins : row %d"), Player, X);
		bIsGameEnd = 1;
		WinPlayer = Player;
		return;
	}

	if (Board[0][Y] == Player && Board[1][Y] == Player && Board[2][Y] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins : column %d"), Player, Y);
		bIsGameEnd = 1;
		WinPlayer = Player;
		return;
	}

	if (X == Y && Board[0][0] == Player && Board[1][1] == Player && Board[2][2] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins"), Player);
		bIsGameEnd = 1;
		WinPlayer = Player;
		return;
	}

	if (X + Y == 2 && Board[0][2] == Player && Board[1][1] == Player && Board[2][0] == Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player %d wins"), Player);
		bIsGameEnd = 1;
		WinPlayer = Player;
		return;
	}

	bool bBoardFull = true;
	for (int32 i = 0; i < 3; i++)
	{
		for (int32 j = 0; j < 3; j++)
		{
			if (Board[i][j] == 0)  
			{
				bBoardFull = false;
				break;
			}
		}
	}

	if (bBoardFull)
	{
		bIsGameEnd = 2;
		UE_LOG(LogTemp, Warning, TEXT("The game is a draw"));
	}
}

