// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalActor.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//purpose of this actor is to act as a goal for the player to get to. Most of this will likely be done in blueprints to save time.
	GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Goal Mesh"));
	GoalMesh->SetupAttachment(RootComponent);
	GoalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	GoalCollision->SetBoxExtent(FVector(80.0f, 80.0f, 80.0f));
	GoalCollision->SetCollisionProfileName("Trigger");
	GoalCollision->SetupAttachment(GoalMesh);
	GoalCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	GoalCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnOverlapBegin);//calling the collision
	GoalCollision->OnComponentEndOverlap.AddDynamic(this, &AGoalActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AGoalActor::BeginPlay()
{
	Super::BeginPlay();
	//PlayerCharacter = Cast<APlayerCharacter>(GetPawn());//Getting the pawn of the player for collision purposes !Currently won't work commenting out for now
	GameModeRef = Cast<AOdysseusGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AGoalActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated Collision"));
	GameModeRef->ScoreIncrease(200.0f);//Increasing score
	//calling the game mode level select function to change levels
	FString CurrentLevel = GetWorld()->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);//UE adds a prefix to the map names gotten from GetMapName so we need to remove that to get the "true" level name.
	if (CurrentLevel == FString("Lvl_Main"))
	{
		GameModeRef->LevelSelect(1.0f);
	}
	if (CurrentLevel == FString("Lvl_Void"))
	{
		GameModeRef->LevelSelect(2.0f);
	}
}

void AGoalActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Collision Ended"));
}

