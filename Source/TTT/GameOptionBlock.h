// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TTTGameManager.h"
#include "GameFramework/Actor.h"
#include "GameOptionBlock.generated.h"

UCLASS()
class TTT_API AGameOptionBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameOptionBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BlockMesh;

	void OnBlockClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	UTTTGameManager* GameManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	FString OptionType;  
};
