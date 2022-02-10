// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEUS_API ABasicEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
protected:
	void BeginPlay();
public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
		TArray<AActor*> Waypoints;
	UFUNCTION()
		AActor* ChooseWaypoints();
	UFUNCTION()
		void RandomPatrol();
};
