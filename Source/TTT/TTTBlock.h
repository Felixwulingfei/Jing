// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "TTTBlock.generated.h"
class UTTTGameManager;


UCLASS()
class TTT_API ATTTBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTTBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Function to handle block click
	UFUNCTION()
	void BlockClicked(int PlayerNum);
	
	UFUNCTION()
	void BlockChangeColor(int PlayerNum);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	int32 Y;

	UTTTGameManager* GameManager;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* BlockMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInstance* MaterialInstance_Empty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInstance* MaterialInstance_Player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInstance* MaterialInstance_Player2;
};
