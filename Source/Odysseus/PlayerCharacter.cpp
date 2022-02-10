// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "RifleActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pcMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PC MESH"));
	pcMesh->SetupAttachment(RootComponent);

	//Camera Setup

	//creating springarm to ensure camera handles obstructions
	USpringArmComponent* armComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamSpringArm"));
	armComponent->SetupAttachment(RootComponent);
	armComponent->TargetArmLength = 200.0f;
	armComponent->SetRelativeLocationAndRotation(FVector(0.0f, 75.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f));
	PlayerCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Cam"));
	PlayerCam->SetupAttachment(armComponent, USpringArmComponent::SocketName);
	//Minimap springarm
	USpringArmComponent* minimapArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniMap Arm"));
	minimapArm->SetupAttachment(RootComponent);
	minimapArm->TargetArmLength = 600.0f;
	minimapArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-90.0f, 0.0f, 0.0f));
	//minimap scene component. Set up above the players head. Projects the image it capture into a HUD element making a minimap type thingy.
	miniMap = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Minmap SceneCap"));
	miniMap->SetupAttachment(minimapArm, USpringArmComponent::SocketName);
	//starts as false to prevent player jumping on spawn.
	isJumping = false;
	



}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (rifleClass != NULL)// making sure a rifle class is assigned in editor
	{
		// getting actor coords to spawn the gun in the right place
		const FRotator SpawnRotation = GetControlRotation();
		const FVector SpawnLocation = GetActorLocation();

		//spawn collision override
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParams.Owner = this;
		//actually spawning the thing
		gun = GetWorld()->SpawnActor<ARifleActor>(rifleClass, SpawnLocation, SpawnRotation, actorSpawnParams);
		//attaching gun to skeleton
		gun->AttachToComponent(pcMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("hand_r"));
		gun->SetActorRelativeLocation(FVector(-19.0f, 0.0f, 0.0f));

	}
	/*Setting the Players Health Variables*/
	Health = MaxHealth;
	Ammo = MaxAmmo;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


int APlayerCharacter::GetHealth(int hp)
{
	return hp;
}
void APlayerCharacter::DmgTimer()
{
}

//PLayer Controller Input Methods
void APlayerCharacter::MoveForwards(float AxisAmount)
{
	AddMovementInput(GetActorForwardVector() * AxisAmount);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootSteps, GetActorLocation(), 1.0f, 1.0f, 0.0f);// playing footsteps when the player walks
}

void APlayerCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);

}

void APlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);

}

void APlayerCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

	void APlayerCharacter::checkJump()
	{
		if (isJumping)
		{
			isJumping = false;
		}
		else
		{
			isJumping = true;
		}
	}

	void APlayerCharacter::BeginFire()
	{

		gun->OnBeginFire();//calling the fire function inside the gun. Easier to retroactively change the code to support multiple guns.
	}
	void APlayerCharacter::EndFire()
	{

		gun->OnEndFire();//calling the fire function inside the gun. Easier to retroactively change the code to support multiple guns.
	}

	int APlayerCharacter::GetAmmo(int AmmoAmount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ammo: %f"), AmmoAmount);
		return AmmoAmount;
	}

	float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
	{
		UE_LOG(LogTemp, Warning, (TEXT("Damage Taken")));
		Health -= DamageAmount;
		if (Health <= 0)
		{
			gun->Destroy();
			Destroy();
		}
		return DamageAmount;
	}


