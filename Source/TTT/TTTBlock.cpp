// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTBlock.h"

#include "TTTGameManager.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ATTTBlock::ATTTBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	RootComponent = BlockMesh;

	BlockMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BlockMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	BlockMesh->SetCollisionObjectType(ECC_WorldDynamic);
	
}

void ATTTBlock::BlockClicked(int PlayerNum)
{
	if (bIsMarked) return;
	if (GameManager)
	{
		GameManager->HandleMove(X, Y);
		BlockChangeColor(PlayerNum);
	}
}

void ATTTBlock::BlockChangeColor(int PlayerNum)
{
	
	if (MaterialInstance_Player1 && MaterialInstance_Empty && MaterialInstance_Player2)
	{
		switch (PlayerNum)
		{
			case (1):
			{	
				BlockMesh->SetMaterial(0, MaterialInstance_Player1);
				break;
			}
			case (2):
			{	
				BlockMesh->SetMaterial(0, MaterialInstance_Player2);
				break;
			}
		}
		bIsMarked = true;
	}
}

// Called when the game starts or when spawned
void ATTTBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTTBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

