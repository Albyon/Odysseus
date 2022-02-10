// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayerHUD.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCController.generated.h"


class APlayerCharacter;
class ARifleActor;

UCLASS()
class ODYSSEUS_API APCController : public APlayerController
{
	GENERATED_BODY()	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//constructor
	APCController();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupInputComponent();
	UFUNCTION()
	void CallForwards(float AxisAmount);
	UFUNCTION()
	void CallStrafe(float AxisAmount);
	UFUNCTION()
	void CallLookUp(float AxisAmount);
	UFUNCTION()
	void CallTurn(float AxisAmount);
	UFUNCTION()
	void CallCheckJump();
	UFUNCTION()
	void CallBeginFire();
	UFUNCTION()
		void CallEndFire();
	UFUNCTION(BlueprintPure)
		int GetHealth();
	UFUNCTION(BlueprintPure)
		int GetAmmo();
	//HUD declarations
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> GameplayHUDClass;
	
	UPROPERTY()
		UUserWidget* HealthHUD;
	

	APlayerCharacter* myPC;

	ARifleActor* myGun;


};

