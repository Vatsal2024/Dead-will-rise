// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationifSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_PlayerLocationifSeen::UBTService_PlayerLocationifSeen() {
	NodeName = "PlayerLocation If Seen";
}


void UBTService_PlayerLocationifSeen::TickNode(UBehaviorTreeComponent& Owner, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(Owner, NodeMemory, DeltaSeconds);
	//
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		if (Owner.GetAIOwner()) {
			bool line = Owner.GetAIOwner()->LineOfSightTo(PlayerPawn);
			if (line) {
				Owner.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
				//SetFocus(PlayerPawn);

		//		MoveToActor(PlayerPawn, AcceptanceRadius);
			}
			else {
				Owner.GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
			}
		}
	}

}
