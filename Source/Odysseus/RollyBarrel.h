// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollyBarrel.generated.h"
class URadialForceComponent;
UCLASS()
class ODYSSEUS_API ARollyBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollyBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditAnywhere)
		URadialForceComponent* ForceComponent;
	UPROPERTY(EditAnywhere)
		float ForceAmount = 950.0f;
	UPROPERTY(EditAnywhere)
		float TorqueAmount = 10.0f;
};
