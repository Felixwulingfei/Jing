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
			if (GameManager->GameMode == EGameMode::GM_AIVsPlayer)
			{
				GameManager->GameMode = EGameMode::GM_LocalPlayerVsPlayer;
			}
			else
			{
				GameManager->GameMode = EGameMode::GM_AIVsPlayer;
			}
		}
		else if (OptionType == "Difficulty")
		{
			if (GameManager->DifficultyLevel == EDifficultyLevel::DL_Easy)
			{
				GameManager->DifficultyLevel = EDifficultyLevel::DL_Hard;
			}
			else
			{
				GameManager->DifficultyLevel = EDifficultyLevel::DL_Easy;
			}
		}
	}
}