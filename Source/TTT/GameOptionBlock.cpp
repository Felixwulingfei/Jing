// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOptionBlock.h"

// Sets default values
AGameOptionBlock::AGameOptionBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;
}

// Called when the game starts or when spawned
void AGameOptionBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameOptionBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameOptionBlock::OnBlockClicked()
{
	if (GameManager)
	{
		if (OptionType == "Mode")
		{
			// Toggle between AI vs Player and Local Player vs Player
			if (GameManager->GameMode == EGameMode::GM_AIVsPlayer)
			{
				GameManager->GameMode = EGameMode::GM_LocalPlayerVsPlayer;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Local Player vs Player mode"));
			}
			else
			{
				GameManager->GameMode = EGameMode::GM_AIVsPlayer;
				UE_LOG(LogTemp, Warning, TEXT("Switched to AI vs Player mode"));
			}
		}
		else if (OptionType == "Difficulty")
		{
			// Toggle between Easy and Hard difficulty
			if (GameManager->DifficultyLevel == EDifficultyLevel::DL_Easy)
			{
				GameManager->DifficultyLevel = EDifficultyLevel::DL_Hard;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Hard difficulty"));
			}
			else
			{
				GameManager->DifficultyLevel = EDifficultyLevel::DL_Easy;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Easy difficulty"));
			}
		}
	}
}