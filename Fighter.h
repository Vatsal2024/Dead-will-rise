// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Fighter.generated.h"

/**
 * 
 */
UCLASS()
class CRYPTRAIDER_API AFighter : public ABasePawn
{
	GENERATED_BODY()

public:
	AFighter();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float Distance=800;

	FTimerHandle FireRateTimerHandle;
	UPROPERTY(EditDefaultsOnly)
	float FireRate = 2.f;
	void CheckFireCondition();

	bool FireInRange();

	void HandleDestruction();
	AActor* BelicaActor;

protected:
	class Atank* Tank;
	class AAvator* Avator;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		//TSubclassOf<class AActor> Belica;
};
