// Fill out your copyright notice in the Description page of Project Settings.

#include "OdysseusGameModeBase.h"
#include "AIZombie.h"

// Sets default values
AAIZombie::AAIZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ZombieMesh"));
	PawnMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAIZombie::BeginPlay()
{
	Super::BeginPlay();
	//Set is dead to be false by default for obvious reasons
	bIsDead = false;
	GameModeRef = Cast<AOdysseusGameModeBase>(GetWorld());
	Health = PawnMaxHealth;
}

// Called every frame
void AAIZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Checks every tick to see if the pawn is dead.If so award points
	if (bIsDead == false)
	{
		return;
	}
	else
	{
		GameModeRef->ScoreIncrease(PointValue);
	}

}
float AAIZombie::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, (TEXT("Damage Taken")));
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}

