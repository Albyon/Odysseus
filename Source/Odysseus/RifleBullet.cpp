// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "RifleBullet.h"
#include "enemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ARifleBullet::ARifleBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	//fire hit event upon collision
	BulletMesh->SetNotifyRigidBodyCollision(true);
	
	BulletMesh->SetSimulatePhysics(true);
	//Projectile Initialisation
	ProjMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	//projectile movement
	ProjMovement->MaxSpeed = ProjSpeed;
	ProjMovement->InitialSpeed = ProjSpeed;
	InitialLifeSpan = 3.0f;//3 second lifespan to ensure quick but not immediate deletion.
}

// Called when the game starts or when spawned
void ARifleBullet::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ARifleBullet::OnHit);
}

// Called every frame
void ARifleBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ARifleBullet::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();
		if (ProjectileOwner == NULL)
		{
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Collision Begin"));
		//Deals damage to the enemy pawn and the enemy class that is a child of the pc class
		if (OtherActor->GetClass()->IsChildOf(AenemyPawn::StaticClass()) || OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()) )
		{
			UE_LOG(LogTemp, Warning, (TEXT("Damage occured")));
			UGameplayStatics::ApplyDamage(
				OtherActor, //actor that will be damaged
				BaseDamage, //the base damage to apply
				ProjectileOwner->GetInstigatorController(), //controller that caused the damage
				this, //Actor that actually caused the damage
				UDamageType::StaticClass() //class that describes the damage that was done
			);
			Destroy();
		}
		
}

