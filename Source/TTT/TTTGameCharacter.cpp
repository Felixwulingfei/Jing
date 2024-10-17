// Fill out your copyright notice in the Description page of Project Settings.


#include "TTTGameCharacter.h"

#include "TTTBlock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATTTGameCharacter::ATTTGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameManager = CreateDefaultSubobject<UTTTGameManager>(TEXT("GameManager"));
}

// Called when the game starts or when spawned
void ATTTGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeBoard();
}

// Called every frame
void ATTTGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTTGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATTTGameCharacter::InitializeBoard()
{
	FVector BlockLocation;
	FActorSpawnParameters SpawnParams;

	for (int32 X = 0; X < 3; X++)
	{
		for (int32 Y = 0; Y < 3; Y++)
		{
			BlockLocation = FVector(X * 200.f + 1000, Y * 200.f + 1000, 0.f);  // Adjust spacing as necessary
			ATTTBlock* NewBlock = GetWorld()->SpawnActor<ATTTBlock>(BlockClass.Get(), BlockLocation, FRotator::ZeroRotator, SpawnParams);


			// Set block properties
			if (NewBlock)
			{
				NewBlock->X = X;
				NewBlock->Y = Y;
				NewBlock->GameManager = GameManager;
			}
		}
	}
}

void ATTTGameCharacter::PerformMouseClickTrace()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController) return;

	FVector WorldLocation, WorldDirection;
	if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.f);  // Set the trace distance to 10,000 units

		FHitResult HitResult;

		// Perform the line trace
		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.IsValidBlockingHit())
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());

				// If the hit actor is a block (ATTTBlock)
				if (ATTTBlock* Block = Cast<ATTTBlock>(HitActor))
				{
					Block->OnBlockClicked(nullptr, FKey());  // Trigger block clicked logic
				}

				// Optionally draw debug line to visualize the trace
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
				DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Green, false, 2.0f);
			}
		}
	}
}