// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBoardValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBoardValue::UBTTask_ClearBoardValue() {
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBoardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}
