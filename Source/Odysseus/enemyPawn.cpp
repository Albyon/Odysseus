// Fill out your copyright notice in the Description page of Project Settings.


#include "enemyPawn.h"

// Sets default values
AenemyPawn::AenemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Mesh"));
	pawnMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AenemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AenemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AenemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AenemyPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Take damage called"));
	return DamageAmount;
}

