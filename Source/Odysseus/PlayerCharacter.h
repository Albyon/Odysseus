// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PCController.h"
#include "RifleActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h" //Unreal was having a hissy fit so had to include this
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"
class UCameraComponent;
class USceneCaptureComponent;
UCLASS()
class ODYSSEUS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* pcMesh;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCam;
	UPROPERTY(VisibleAnywhere)
		USceneCaptureComponent* miniMap;
	
	class ARifleActor* gun;
	//BEGIN HEALTH VAR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Health")
		int MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Health")
		int Health;
	UFUNCTION(BlueprintPure, Category = "PCHealth")
		int GetHealth(int hp);
	//BEGIN Ammo VAR
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		int MaxAmmo = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		int Ammo;
	UFUNCTION(BlueprintPure)
		int GetAmmo(int AmmoAmount);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC Ammo")
		int AmmoDecrement = 1;

	//The following functions will use a Timer to grant the player temporary immunity to damage upon being hit
	UFUNCTION()
		void DmgTimer();
	
	//Control Functions
	UFUNCTION()
		void MoveForwards(float AxisAmount);
	UFUNCTION()
		void Strafe(float AxisAmount);
	UFUNCTION()
		void LookUp(float AxisAmount);
	UFUNCTION()
		void Turn(float AxisAmount);
	UFUNCTION()
		void checkJump();
	UPROPERTY()
		bool isJumping;
	UFUNCTION()
		void BeginFire();
	UFUNCTION()
		void EndFire();
	
	//Action UI
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HelperWidgetClass;
	class UUWidget* HelpyWidget;
	UPROPERTY(EditAnywhere)
		USoundBase* FootSteps;
	
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ARifleActor> rifleClass;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;


};