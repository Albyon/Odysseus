// Copyright Epic Games, Inc. All Rights Reserved.


#include "OdysseusGameModeBase.h"
#include "PCController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerHUD.h"



void AOdysseusGameModeBase::GameStateHandler(EGameState NewGameState)
{
	switch (NewGameState)
	{
	case EGameState::EPlay:
	{
		//do nothing let game proceed as normal
	}
	break;
	case EGameState::EGameOver:
	{
		//go to the GameOver Level where the Gameover screen will show
		UGameplayStatics::OpenLevel(this, FName(TEXT("Lvl_GameOver"), false));

	}
	break;
	default:
	case EGameState::EOther:
	{
		//do nothing except log the error because this shouldn't happen
		UE_LOG(LogTemp, Warning, TEXT("THIS SHOULDN'T HAPPEN AAAAAAAAAAHHHH HELP!!!!"));
	}
	}
}

AOdysseusGameModeBase::AOdysseusGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	//use player controller class
	PlayerControllerClass = APCController::StaticClass();
	//use cpp HUD
	HUDClass = APlayerHUD::StaticClass();
}



void AOdysseusGameModeBase::ScoreIncrease(float ToAdd)
{
	Score += ToAdd;//Adds to the score based upon what is inputted. Done this way so I can give different accomplishments different score values without multiple 
	UE_LOG(LogTemp, Warning, TEXT("Score %f"), Score);
}

void AOdysseusGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//world load check
	if (GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("World Loaded"));
		GetWorld()->GetTimerManager().SetTimer(EndGameTimer, this, &AOdysseusGameModeBase::TimeUp, GameDuration, false);
	}
	//Ensuring the game state is set to the gameplay state upon loading
	
	SetGameState(EGameState::EPlay);
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
}
void AOdysseusGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*Tick will primarily be used to check if the player has run out of Health*/
	if (Player)
	{
		if (Player->Health <= 0)
		{
			SetGameState(EGameState::EGameOver);
		}
	}
	
}

EGameState AOdysseusGameModeBase::GetGameState() const
{
	//pretty self explanatory
	return CurrentGameState;
}

void AOdysseusGameModeBase::SetGameState(EGameState NewGameState)
{
	//Setting current state as the one passed into function and passing it inot the handler function.
	CurrentGameState = NewGameState;
	GameStateHandler(CurrentGameState);

}

void AOdysseusGameModeBase::LevelSelect(float LevelID)
{
	//Cannot be a switch as it uses a float value and not an integral or an ENum.
	//This code checks the inputted level ID against the ones in the if statements. If it matches one it loads that level, If it doesnt it prints an Error Message to Console. Using an if statement also allows
	if (LevelID == 0.0f)//Checks Level ID
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Lvl_Main");//Loads the Main Test Level/ Tutorial
		GameDuration = 300.0f;
	}
	if (LevelID == 1.0f)//Checks Level ID
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Lvl_Void");//Loads the Second Level, The Void a Jumping Puzzle based map
		GameDuration = 300.0f; //Resetting timer
	}
	if (LevelID == 2.0f)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Lvl_GameOver");//Loads the game over menu
		//do not need to reset the timer since the game is over.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR, INVALID LEVEL ID"));
	}

}

void AOdysseusGameModeBase::TimeUp()
{
	//If time is up end the game
	UE_LOG(LogTemp, Warning,(TEXT("TIME UP CALLED")));
	SetGameState(EGameState::EGameOver);
}

	

	