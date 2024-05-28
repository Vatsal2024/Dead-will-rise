// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRaiderGameMode.h"
#include "CryptRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "tank.h"
#include "ToonTanksPlayerController.h"
#include "fighter.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ACryptRaiderGameMode::ActorDied(AActor* DeadActor)
{
	if (AFighter* DestroyedFighter = Cast<AFighter>(DeadActor)) {
		DestroyedFighter->HandleDestruction();
	}
}



