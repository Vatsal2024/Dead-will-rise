// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;
	APawn* PlayerPawn;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius=200;
};
