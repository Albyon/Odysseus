// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "FixedAIZombie.h"
#include "OdysseusGameModeBase.h"
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
	
	AmmoInMag = 30;
	AmmoReserve = 30;
	bCanShoot = true
		;//determines if the player can shoot. As they spawn in with ammo this is set to true

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
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Health <= 0)
	{
		GameMode->LevelSelect(2.0f);
	}

}


int APlayerCharacter::GetHealth(int hp)
{
	return hp;
}
void APlayerCharacter::OnReload()
{
	if (AmmoReserve <= 0 || AmmoInMag >= 30)
	{
		return;//we dont need to reload if the player is out of ammo or has a full magazine and so it returns
	}
	if (AmmoReserve < 30)
	{
		// Adds what remains in the ammo reserve pool to the loaded ammo and sets reserve to zero. This is to be used if the player has less than 30 bullets in the ammo pool but still wants to reload
		AmmoInMag = AmmoInMag + AmmoReserve;
		AmmoReserve = 0;
	}
	else
	{
		//reduces ammo reserve by (30 - AmmoInMag). This means that it wont always remove 30 bullets from the reserve pool but instead removes how ever many bullets are missing from the magazine
		AmmoReserve = AmmoReserve - (30 - AmmoInMag);
		AmmoInMag = 30;
		

	}
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
	//UE_LOG(LogTemp, Warning, TEXT("UPCALL"));

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
		if (AmmoInMag <= 0)
		{
			bCanShoot = false;
			return;//no ammo cant shoot  :(
		}
		else if (bCanShoot == true)
		{
			AmmoInMag = AmmoInMag - 1;//Decreasing on fire
			AController* ControllerRef = GetController();
			
			//Getting the location of the camera for Raycasting.
			ControllerRef->GetPlayerViewPoint(CameraLocal, CameraRot);
			FVector End = CameraLocal + CameraRot.Vector() * CastRange;//End point of the raycasting.
			bDidHit = GetWorld()->LineTraceSingleByChannel(Hit, CameraLocal, End, ECC_Visibility);
			if (GunShot != NULL)
			{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunShot, GetActorLocation(), 1.0f, 1.0f, 0.0f); //plays a gun shot sound
			}
			
			
			if (bDidHit)
			{
				//tells us in the log the name of what actor the ray hit.
				UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
				UPrimitiveComponent* RootComp = Cast<UPrimitiveComponent>(Hit.GetActor()->GetRootComponent());//Downcasting to get the primitive RootComp
				RootComp->AddImpulse(CameraRot.Vector() * ImpulseForce * RootComp->GetMass());//CameraRot used to add impulse at same vector as used in the raycast. This line is calculating what is needed for adding Impulse physics to an object;
				if (Hit.GetActor()->GetClass()->IsChildOf(AFixedAIZombie::StaticClass()) || Hit.GetActor()->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
				{
					UE_LOG(LogTemp, Warning, (TEXT("Damage occured")));
					UGameplayStatics::ApplyDamage(
						Hit.GetActor(), //actor that will be damaged
						BaseDamage, //the base damage to apply
						GetInstigatorController(), //controller that caused the damage
						this, //Actor that actually caused the damage
						UDamageType::StaticClass() //class that describes the damage that was done
					);
					
				}
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Missed"));
			}

			//gun->OnBeginFire();//calling the fire function inside the gun. Easier to retroactively change the code to support multiple guns. Not needed anymore due to raycasting but kept commented in as a backup
		}
		
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

	


