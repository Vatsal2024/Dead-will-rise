// Fill out your copyright notice in the Description page of Project Settings.
#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent *PhysicsHandle=GetPhysicsHandle();
	if(PhysicsHandle->GetGrabbedComponent()!=nullptr){
		FVector ComponentLocation = GetComponentLocation();
		ComponentLocation.Z += 50;
		FVector TargetLocation = ComponentLocation + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation,GetComponentRotation());
	}
}

void UGrabber:: Release(){
	// UE_LOG(LogTemp, Display, TEXT("Released my boyyyyy......."));
	UPhysicsHandleComponent *PhysicsHandle=GetPhysicsHandle();
	UPrimitiveComponent* getComponent=PhysicsHandle->GetGrabbedComponent();
	if(getComponent!=nullptr){
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		getComponent->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber:: Grab(){
	FHitResult OutResult;
	bool OuthasHit;
	GetGrabbableInReach(OuthasHit,OutResult);
	UPhysicsHandleComponent *PhysicsHandle=GetPhysicsHandle();
	if (OuthasHit){
		UPrimitiveComponent* HitComponent=OutResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		OutResult.GetActor()->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			OutResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}


void UGrabber:: GetGrabbableInReach(bool& OuthasHit, FHitResult& OutResult){
	UWorld* World=GetWorld();

	FVector Start= GetComponentLocation();
	FVector End=Start + GetForwardVector()*Distance;

	FCollisionShape Sphere= FCollisionShape::MakeSphere(GrabRadius);

	UPhysicsHandleComponent *PhysicsHandle=GetPhysicsHandle();

	OuthasHit= GetWorld()->SweepSingleByChannel(
		OutResult,
		Start, End,
		FQuat:: Identity,
		ECC_GameTraceChannel2,
		Sphere
	);
}



UPhysicsHandleComponent* UGrabber:: GetPhysicsHandle() const{
	UPhysicsHandleComponent* PhysicsHandle= GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle==nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a Physics Handle"));
		// return 0;
	}
	return PhysicsHandle;
}


