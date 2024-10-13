// Copyright Epic Games, Inc. All Rights Reserved.

#include "TTTGameMode.h"
#include "TTTPlayerController.h"
#include "TTTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATTTGameMode::ATTTGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATTTPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}