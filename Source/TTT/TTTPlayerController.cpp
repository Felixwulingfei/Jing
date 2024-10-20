// Copyright Epic Games, Inc. All Rights Reserved.

#include "TTTPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TTTCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameOptionBlock.h"
#include "TTTBlock.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATTTPlayerController::ATTTPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
	
	GameManager = CreateDefaultSubobject<UTTTGameManager>(TEXT("GameManager"));
}

void ATTTPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	InitializeBoard();
}

void ATTTPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ATTTPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ATTTPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ATTTPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ATTTPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ATTTPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ATTTPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ATTTPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ATTTPlayerController::OnTouchReleased);

		
		EnhancedInputComponent->BindAction(SeTLaserAction, ETriggerEvent::Triggered, this, &ATTTPlayerController::PerformMouseClickTrace);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATTTPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATTTPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATTTPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ATTTPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ATTTPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ATTTPlayerController::InitializeBoard()
{
	FVector BlockLocation;
	FActorSpawnParameters SpawnParams;

	for (int32 X = 0; X < 3; X++)
	{
		for (int32 Y = 0; Y < 3; Y++)
		{
			BlockLocation = FVector(X * 200.f + 1000, Y * 200.f + 1000, 0.f); 
			ATTTBlock* NewBlock = GetWorld()->SpawnActor<ATTTBlock>(BlockClass.Get(), BlockLocation, FRotator::ZeroRotator, SpawnParams);


			// Set block properties
			if (NewBlock)
			{
				NewBlock->X = X;
				NewBlock->Y = Y;
				NewBlock->GameManager = GameManager;
				
				GameManager->Blocks.Add(NewBlock);
			}
		}
	}
	
	BlockLocation = FVector(800.f, 1500.f, 0.f); 
	AGameOptionBlock* ModeBlock = GetWorld()->SpawnActor<AGameOptionBlock>(ModeBlockClass.Get(), BlockLocation, FRotator::ZeroRotator, SpawnParams);
	if (ModeBlock)
	{
		ModeBlock->GameManager = GameManager;
	}

	BlockLocation = FVector(800.f, 1700.f, 0.f);
	AGameOptionBlock* DifficultyBlock = GetWorld()->SpawnActor<AGameOptionBlock>(DifficultyBlockClass.Get(), BlockLocation, FRotator::ZeroRotator, SpawnParams);
	if (DifficultyBlock)
	{
		DifficultyBlock->GameManager = GameManager;
	}
}

void ATTTPlayerController::PerformMouseClickTrace()
{
	if (bIsCooldownActive) return;
	
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ATTTPlayerController::ResetCooldown, CooldownDuration, false);
	FVector WorldLocation, WorldDirection;
	if (this->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector TraceStart = WorldLocation;
		FVector TraceEnd = TraceStart + (WorldDirection * 10000.f);

		FHitResult HitResult;

		GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

		if (HitResult.IsValidBlockingHit())
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				if (ATTTBlock* Block = Cast<ATTTBlock>(HitActor))
				{
					Block->BlockClicked(GameManager->CurrentPlayer);
					bIsCooldownActive = true;
				}
				if (AGameOptionBlock* Block = Cast<AGameOptionBlock>(HitActor))
				{
					Block->OnBlockClicked(); 
					bIsCooldownActive = true;
				}
				
				DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
				DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Green, false, 2.0f);
			}
		}
	}
}

void ATTTPlayerController::ResetCooldown()
{
	bIsCooldownActive = false;
}