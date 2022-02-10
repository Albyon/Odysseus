// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "PCController.h"
#include "Components/InputComponent.h"

#include "RifleActor.h"

APCController::APCController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
void APCController::BeginPlay()
{
	Super::BeginPlay();
	myPC = Cast<APlayerCharacter>(GetPawn());
	myGun = Cast<ARifleActor>(GetPawn());
	
	/*HealthHUD = CreateWidget(this, GameplayHUDClass);
	* //AmmoHUD = CreateWidget(this, GameplayHUDClass);
	if (HealthHUD != nullptr)//some safety to prevent editor classes.
	{
		HealthHUD->AddToViewport();//adding to viewpirt
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), myPC->Health);
	}
	*/
	
	
}


void APCController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (myPC)
	{
		if (myPC->isJumping)
		{
			//Unreal has a built in jump function, I definitely didn't find this out after half an hour of failing to get a jump to work properly. 
			//Note: Height should be controllable from the editor.
			//Using a boolean so the player can't do something stupid like an infinite equivalent of a double jump.

			myPC->Jump();
		}
	}
	
}

void APCController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	//calling controller input methods so player can move
	InputComponent->BindAxis(TEXT("MoveForwards"), this, &APCController::CallForwards);
	InputComponent->BindAxis(TEXT("Strafe"), this, &APCController::CallStrafe);
	InputComponent->BindAxis(TEXT("LookUp"), this, &APCController::CallLookUp);
	InputComponent->BindAxis(TEXT("Turn"), this, &APCController::CallTurn);
	//jump components. Called on both press and release
	InputComponent->BindAction("Jump", IE_Pressed, this, &APCController::CallCheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &APCController::CallCheckJump);
	//firing gun
	InputComponent->BindAction("Fire", IE_Pressed, this, &APCController::CallBeginFire);
	InputComponent->BindAction("Fire", IE_Released, this, &APCController::CallEndFire);
}

void APCController::CallForwards(float AxisAmount)
{
	if (myPC)
	{
		myPC->MoveForwards(AxisAmount);
	}
}

void APCController::CallStrafe(float AxisAmount)
{
	if (myPC)
	{
		myPC->Strafe(AxisAmount);
	}
}

void APCController::CallLookUp(float AxisAmount)
{
	if (myPC)
	{
		myPC->LookUp(AxisAmount);
	}
}

void APCController::CallTurn(float AxisAmount)
{
	if (myPC)
	{
		myPC->Turn(AxisAmount);
	}
}

void APCController::CallCheckJump()
{
	if (myPC)
	{
		myPC->checkJump();
	}
}

void APCController::CallBeginFire()
{
	if (myPC)
	{
		
		myPC->BeginFire();
	}
}
void APCController::CallEndFire()
{
	if (myPC)
	{

		myPC->EndFire();
	}
}

int APCController::GetHealth()
{
	int HP;
	HP = myPC->GetHealth(myPC->Health);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), HP);
	return HP;
}

int APCController::GetAmmo()
{

	return 0;
}
