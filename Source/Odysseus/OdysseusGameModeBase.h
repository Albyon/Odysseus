// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include"PlayerCharacter.h"
#include "RifleActor.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OdysseusGameModeBase.generated.h"

/**
 * 
 */
/*Some ENUMS because I wanted to see how they worked in Unreal, could have been done without but I have apparently made a habit of overcomplicated stuff in this assignment *shrug* */
UENUM()
enum class EGameState
{
	EPlay,
	EGameOver,
	EOther//failsafe state, should never be called but this code has been redone a bunch of times to the point it feels like it might have more spaghetti than the Italian Peninsula.
};
UCLASS()
class ODYSSEUS_API AOdysseusGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	/*Timer Stuff to make the game timed*/
	FTimerHandle EndGameTimer;
	UPROPERTY(EditAnywhere, Category = GameRules)
		float GameDuration = 300.0f; //gives the player 5 minutes to play level
	UFUNCTION()
		void TimeUp();
	/*GameState Tracking*/
	EGameState CurrentGameState;

	/*Anything that requires a gamestate to be called goes in this function, i.e gameover stuff*/
	void GameStateHandler(EGameState NewGameState);
	
	
public:
	AOdysseusGameModeBase();
	UPROPERTY(EditAnywhere, Category = PlayerStatistic)
		float PlayerHealth;
	
	UPROPERTY(EditAnywhere, Category = PlayerStatistic)
		bool GameLost;
	UPROPERTY(EditAnywhere, Category = PlayerStatistic)
		bool GameWon;
	UPROPERTY(EditAnywhere, Category = PlayerStatistic)
		float Score;
	class APlayerCharacter* Player;
	UFUNCTION()
		void ScoreIncrease(float ToAdd);
	UFUNCTION()
		virtual void BeginPlay() override;
	UFUNCTION()
		virtual void Tick(float DeltaTime) override;
	/*Return GameState*/
	UFUNCTION(BlueprintPure)
		EGameState GetGameState() const;
	/*new GameState*/
	UFUNCTION()
	void SetGameState(EGameState NewGameState);
	UFUNCTION()
		void LevelSelect(float LevelID);//0 for Main test level/Tutorial, 1 for First level etc.

	
};
