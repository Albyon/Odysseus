// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifleBullet.generated.h"

class UProjectileMovementComponent;
UCLASS()
class ODYSSEUS_API ARifleBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifleBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BulletMesh;
	UPROPERTY(EditAnywhere)
		float ProjSpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjMovement;
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	float BaseDamage = 10.0f;
};
