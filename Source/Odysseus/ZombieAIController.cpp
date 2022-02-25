// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();
	//Gets the location of Player 0 (as the game is single player) for the AIController and tells the AI to focus on the Player's Pawn.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//SetFocus(PlayerPawn); //disabled for now to test line of sight
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
	if (BasicBehaviorTree != nullptr)
	{
		RunBehaviorTree(BasicBehaviorTree);
		
		
	}
	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPos"), PlayerPawn->GetActorLocation());
	GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineofSight"), false);
}

void AZombieAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//In tick as well to keep position updated.
	APawn* AIPawn = GetPawn();
	DotProduct(AIPawn, PlayerPawn);
	//line of sight
	
	if (LineOfSightTo(PlayerPawn) && bIsInFront(PlayerPawn))
	{
		UE_LOG(LogTemp, Warning, TEXT("I SEE YOU"));
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPos"), PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineofSight"), true);
		
	}
	else
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("HasLineofSight"), false);
		UE_LOG(LogTemp, Warning, TEXT("SLEEP"));
	}
}

AActor* AZombieAIController::ChooseWaypoints()
{
	int index = FMath::RandRange(0, Waypoints.Num() - 1);
	//GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoints"),Waypoints[index]->GetActorLocation());
	return Waypoints[index];
}

void AZombieAIController::RandomPatrol()
{
	GetBlackboardComponent()->SetValueAsVector(TEXT("Waypoint"), ChooseWaypoints()->GetActorLocation());
}

void AZombieAIController::DotProduct(APawn* AI, APawn* Player)
{
	FVector AIForwardVector = AI->GetActorForwardVector();//get a normalised vectors for the dot product
	FVector PlayerPositionVector = Player->GetActorLocation();
	FVector AIPositionVector = AI->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;//calculating the vector between the two points and then normalising manually in the next line
	AIToPlayerVector.Normalize();

	//Dot Product Calculations
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	//Display Dot Priduct in Log
	//UE_LOG(LogTemp, Warning, TEXT("dot product result: %f"), DirectionDotProduct);//Commented out to prevent log spamming
}

bool AZombieAIController::bIsInFront(AActor* ActorToCheck)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);//In tick as well to keep position updated.
	APawn* AIPawn = GetPawn();
	FVector AIForwardVector = AIPawn->GetActorForwardVector();//get a normalised vectors for the dot product
	FVector PlayerPositionVector = PlayerPawn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;//calculating the vector between the two points and then normalising manually in the next line
	AIToPlayerVector.Normalize();

	//Dot Product Calculations
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);
	//Display Dot Priduct in Log
	UE_LOG(LogTemp, Warning, TEXT("dot product result: %f"), DirectionDotProduct);
	if (DirectionDotProduct > -0.3 )//to give it a wider fov
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

void AZombieAIController::OnMoveCompleted(FAIRequestID RequestID, const
	FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	RandomPatrol();
}
