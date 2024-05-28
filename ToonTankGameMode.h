// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool GameWon);

public:
	virtual void BeginPlay() override;

	void ActorDied(AActor* DeadActor);

	class Atank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay=2.f;
	void HandleGameStart();

	int32 fightercount;
	
};


