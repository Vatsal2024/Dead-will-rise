// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner= GetOwner();
	CurrentLocation= owner->GetActorLocation();
	TargetLocation=CurrentLocation+Distance;
	// UE_LOG(LogTemp,Display,TEXT("CurrentLocation = %s TargetLocation : %s"),*CurrentLocation.ToString(),*TargetLocation.ToString());
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	double Speed=(FVector::Distance(CurrentLocation,TargetLocation))/Time;
	if(ShouldMove){
		// UE_LOG(LogTemp, Display, TEXT("Speed is %f"),Speed);
		FVector UpdatedLocation= FMath:: VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(UpdatedLocation);
		AActor* owner= GetOwner();
		CurrentLocation= owner->GetActorLocation();
		if (CurrentLocation == TargetLocation) {
			DestroyComponent();
		}
	}
	// UE_LOG(LogTemp, Display, TEXT("Location: %s"), *st);
}

