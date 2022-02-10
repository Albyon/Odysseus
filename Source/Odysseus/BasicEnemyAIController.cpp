// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"


void ABasicEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	//Gets the location of Player 0 (as the game is single player) for the AIController and tells the AI to focus on the Player's Pawn.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
}
void ABasicEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//In tick as well to keep position updated.
	//moving zombie to player actor, this will hopefully get them into a realistic melee range so they can "bite" the player and deal damage.
	RandomPatrol();
}

AActor* ABasicEnemyAIController::ChooseWaypoints()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Waypoints[index];
}

void ABasicEnemyAIController::RandomPatrol()
{
	MoveToActor(ChooseWaypoints());
}
void ABasicEnemyAIController::OnMoveCompleted(FAIRequestID RequestID, const
	FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	RandomPatrol();
}

