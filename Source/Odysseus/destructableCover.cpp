// Fill out your copyright notice in the Description page of Project Settings.


#include "destructableCover.h"

// Sets default values
AdestructableCover::AdestructableCover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	coverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("cover mesh"));
}

// Called when the game starts or when spawned
void AdestructableCover::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AdestructableCover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

