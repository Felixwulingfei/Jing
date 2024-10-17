// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTTGameManager.h"
#include "GameFramework/Character.h"
#include "TTTGameCharacter.generated.h"

UCLASS()
class TTT_API ATTTGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATTTGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	// A reference to your GameManager UObject
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	UTTTGameManager* GameManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TSubclassOf<class ATTTBlock> BlockClass;
	
	// Initialize the board with blocks
	void InitializeBoard();
	void PerformMouseClickTrace();
};
