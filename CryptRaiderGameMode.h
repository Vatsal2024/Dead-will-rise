// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CryptRaiderGameMode.generated.h"

UCLASS(minimalapi)
class ACryptRaiderGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACryptRaiderGameMode();
	//virtual void BeginPlay() override;
	void ActorDied(AActor* DeadActor);
	int32 fightercount;
};



