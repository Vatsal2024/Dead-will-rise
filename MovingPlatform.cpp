// Fill out your copyright notice in the Description page of Project Settings.
#include "MovingPlatform.h"
// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation=GetActorLocation();
}
// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovingPlatforms(DeltaTime);
	RotatingPlatforms(DeltaTime);

	
}

void AMovingPlatform::MovingPlatforms(float DeltaTime){
	if (ShouldPlatformReturn()){
		FVector MoveDirection= PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection*MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity= -PlatformVelocity;
	}
	else{
		FVector LocalVector=GetActorLocation();
		// UE_LOG(LogTemp, Warning, TEXT("Float value: %f"), DeltaTime);
		LocalVector=LocalVector+PlatformVelocity*DeltaTime;
		SetActorLocation(LocalVector);
	}
}

void AMovingPlatform::RotatingPlatforms(float Deltatime){
	AddActorLocalRotation(RotationVelocity*Deltatime);
}

bool AMovingPlatform::ShouldPlatformReturn()
{
	return GetDistanceMoved()>MoveDistance;
}

float AMovingPlatform::GetDistanceMoved(){
	Distance= FVector::Dist(StartLocation,GetActorLocation());
	return Distance;
}