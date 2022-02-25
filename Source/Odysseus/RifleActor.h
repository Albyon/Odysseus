// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "RifleBullet.h"
#include "OdysseusGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifleActor.generated.h"

//classes//
class APlayerCharacter;

UCLASS()
class ODYSSEUS_API ARifleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnBeginFire();
	UFUNCTION()
		void OnEndFire();
	/*Ammo fuctions and vars*/
	/*Ammo functions*/
	FTimeline PlayerTimeline;
	float CurveFloatValue;
	float TimelineValue;
	FTimerHandle MemberTimerHandle;
	/*Ammo Variables*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		float MaxAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		float Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		int AmmoDecrement = 1;
	
	
private:
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* rifle;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditAnywhere)
		USoundBase* GunClick;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ARifleBullet> BulletClass;
	
	UPROPERTY()
		class AOdysseusGameModeBase* AmmoRef;
};
