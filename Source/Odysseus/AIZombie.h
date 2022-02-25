// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "OdysseusGameModeBase.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AIZombie.generated.h"

UCLASS()
class ODYSSEUS_API AAIZombie : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
