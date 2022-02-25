// Fill out your copyright notice in the Description page of Project Settings.

#include "OdysseusGameModeBase.h"
#include "FixedAIZombie.h"

// Sets default values
AFixedAIZombie::AFixedAIZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFixedAIZombie::BeginPlay()
{
	Super::BeginPlay();
	bIsDead = false;
	GameModeRef = Cast<AOdysseusGameModeBase>(GetWorld());
	Health = PawnMaxHealth;
}

// Called every frame
void AFixedAIZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDead == false)
	{
		return;
	}
	else
	{
		GameModeRef->ScoreIncrease(PointValue);
	}
}

// Called to bind functionality to input
void AFixedAIZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AFixedAIZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, (TEXT("Damage Taken")));
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}
