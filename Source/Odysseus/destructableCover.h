// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "destructableCover.generated.h"

UCLASS()
class ODYSSEUS_API AdestructableCover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AdestructableCover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//setting up mesh. Will likely just be a cube for timesaving purposes
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* coverMesh;
};
