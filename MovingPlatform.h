// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class CRYPTRAIDER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere,Category="Platform Velocity")
	FVector PlatformVelocity=FVector(0,100,0);

	// UPROPERTY(VisibleAnywhere,Category="Distance Between ")
	double Distance;

	FVector StartLocation;

	UPROPERTY(EditAnywhere)
	float MoveDistance=150.0;

	UPROPERTY(EditAnywhere)
	FRotator RotationVelocity;

	void MovingPlatforms(float Deltatime);
	void RotatingPlatforms(float Deltatime);

	bool ShouldPlatformReturn();

	float GetDistanceMoved();
};
