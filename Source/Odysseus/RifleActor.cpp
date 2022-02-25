// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleActor.h"
#include"PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "OdysseusGameModeBase.h"
// Sets default values
ARifleActor::ARifleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//setup for mesh and spawn points
	rifle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rifle Mesh"));
	rifle->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(rifle);
}  

// Called when the game starts or when spawned
void ARifleActor::BeginPlay()
{
	Super::BeginPlay();
	//Casting a reference to the game mode to access its data(we are mostly concerned with the ammo count here)
	AmmoRef = Cast<AOdysseusGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	
	
	

}

// Called every frame
void ARifleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerTimeline.TickTimeline(DeltaTime);
	
}

void ARifleActor::OnBeginFire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRED"));
	

	if (BulletClass)//if bullet class set, player ammo is NOT nearly zero and they are able to shoot then the gun will fire. This should stop the gun firing when it isn't supposed to i.e no Ammo
	{

		// spawn a bullet actor at the Projectile Spawn Point
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		ARifleBullet* TempBullet = GetWorld()->SpawnActor<ARifleBullet>(BulletClass, SpawnLocation, SpawnRotation);
		TempBullet->SetOwner(this);


	}
	
}
void ARifleActor::OnEndFire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRED"));
}


