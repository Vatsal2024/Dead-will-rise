// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	



	//bool line = LineOfSightTo(PlayerPawn);
	//if (line) {
		
		//GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownLocation"), PlayerPawn->GetActorLocation());
		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		//SetFocus(PlayerPawn);

		//MoveToActor(PlayerPawn, AcceptanceRadius);
	//}
	//else {
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}


}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior) {
		RunBehaviorTree(AIBehavior);
		PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		//GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}
