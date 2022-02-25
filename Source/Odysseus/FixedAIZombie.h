// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FixedAIZombie.generated.h"

UCLASS()
class ODYSSEUS_API AFixedAIZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFixedAIZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* PawnMesh;
	UPROPERTY(EditAnywhere, Category = Stats)
		float PawnMaxHealth = 50.0f;
	UPROPERTY(EditAnywhere, Category = Stats)
		float PointValue = 20.0f;// How points is awarded on death.
	UPROPERTY(EditAnywhere, Category = Stats)
		bool bIsDead;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int Health;
	class AOdysseusGameModeBase* GameModeRef;
private:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

};
