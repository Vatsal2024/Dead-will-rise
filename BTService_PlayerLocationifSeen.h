// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerLocationifSeen.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API UBTService_PlayerLocationifSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_PlayerLocationifSeen();
protected:
	virtual void TickNode(UBehaviorTreeComponent& Owner, uint8* NodeMemory, float DeltaSeconds);
};

