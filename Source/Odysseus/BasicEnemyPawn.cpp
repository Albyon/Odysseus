// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"
//This is for the pawn that cannot shoot and deals damage via melee attacks, It will be coloured green to differentiate it from the rifleman npc from a difference. A Zombie basically.
ABasicEnemyPawn::ABasicEnemyPawn()
{
	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Basic Pawn Mesh"));
	PawnMesh->SetupAttachment(RootComponent);
	//sensing
	

}
void ABasicEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//checking if dead to award points
	if (bIsDead)
	{
		//award points

		//kill
		Destroy();
	}
}

void ABasicEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}
