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
	
	BlockMesh->OnClicked.AddDynamic(this, &ATTTBlock::OnBlockClicked);
	if (BlockMesh->OnClicked.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("BlockMesh OnClicked event bound successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to bind BlockMesh OnClicked event."));
	}
}

void ATTTBlock::OnBlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	if (GameManager)
	{
		GameManager->HandleMove(X, Y);
		
		UMaterialInstanceDynamic* DynamicMaterial = BlockMesh->CreateAndSetMaterialInstanceDynamic(0);

		if (DynamicMaterial)
		{
			FLinearColor Color = FLinearColor(GameManager->Board[X][Y] % 2, 0, GameManager->Board[X][Y] % 2); 
			DynamicMaterial->SetVectorParameterValue("BaseColor", Color);
		}
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

