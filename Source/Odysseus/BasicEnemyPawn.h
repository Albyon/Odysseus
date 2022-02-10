// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "BasicEnemyPawn.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEUS_API ABasicEnemyPawn : public APlayerCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ABasicEnemyPawn();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* pawnMesh;
	UPROPERTY(EditAnywhere, Category = Stats)
		float PawnMaxHealth = 50.0f;
	UPROPERTY(EditAnywhere, Category = Stats)
		float PointValue = 20.0f;// How points is awarded on death.
	UPROPERTY(EditAnywhere, Category = Stats)
		bool bIsDead;


};
