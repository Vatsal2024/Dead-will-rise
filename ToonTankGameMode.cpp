// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "tank.h"
#include "ToonTanksPlayerController.h"
#include "fighter.h"

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, AFighter::StaticClass(), Towers);
	fightercount = Towers.Num();
}

void AToonTankGameMode::HandleGameStart() {
	Tank = Cast<Atank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController) {
		UE_LOG(LogTemp, Warning, TEXT("Toon Tank Game mode active"));
		ToonTanksPlayerController->SetPlayerEnabled(false);
		FTimerHandle TimerHandle;
		FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabled, true);
		GetWorldTimerManager().SetTimer(TimerHandle, InputDelegate, StartDelay, false);
	}

}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor==Tank) {
		Tank->HandleDestruction();
		if (Tank->GetPlayerController()) {
			ToonTanksPlayerController->SetPlayerEnabled(false);
			GameOver(false);
			UE_LOG(LogTemp, Error, TEXT("Game Over false "));
		}
		else {
			UE_LOG(LogTemp,Error,TEXT("Game Mode didn't got access of Playercontroller"))
		}
	}

	else if (AFighter * DestroyedFighter = Cast<AFighter>(DeadActor)) {
		DestroyedFighter->HandleDestruction();
		fightercount = fightercount - 1;
		if (fightercount <= 0) {
			GameOver(true);
			UE_LOG(LogTemp, Error, TEXT("Game Over true "));
		}
	}
	

}
