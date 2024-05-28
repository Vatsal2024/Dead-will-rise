// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Avator.h"

UBTT_Shoot::UBTT_Shoot() {
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner()) {
		AAvator* avator = Cast<AAvator>(OwnerComp.GetAIOwner()->GetPawn());
		avator->Shoot();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	

	
}