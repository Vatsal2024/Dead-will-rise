// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
UBTService_PlayerLocation::UBTService_PlayerLocation() {
	NodeName = "Update PlayerLocation";
}


void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& Owner, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(Owner, NodeMemory, DeltaSeconds);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		Owner.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
}
