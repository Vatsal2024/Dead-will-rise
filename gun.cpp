// Fill out your copyright notice in the Description page of Project Settings.


#include "gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
Agun::Agun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeleton Mesh"));
	Mesh->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void Agun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Agun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Agun::PullTrigger()
{
	//UE_LOG(LogTemp, Display, TEXT("Gun is shooting"));
	if (Mesh)
	{
		if (Mesh->DoesSocketExist(TEXT("FireAnimeSocket")))
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("FireAnimeSocket"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Socket 'FireAnimeSocket' does not exist in GunBody."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GunBody component is null."));
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No Owner Pawn found"));
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No Owner Controller found"));
		return;
	}
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	FHitResult HitResult;
	bool hashit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel:: ECC_GameTraceChannel3,Params);
	if (hashit) {
		FVector RotationAtHit = -Rotation.Vector();
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 12, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleAtHit, HitResult.Location, RotationAtHit.Rotation());
		FPointDamageEvent DamageEvent(DamageAmmount, HitResult, RotationAtHit, nullptr);
		if (HitResult.GetActor()) {
			HitResult.GetActor()->TakeDamage(DamageAmmount, DamageEvent, OwnerController, this);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Didn't hit anything"));
	}
	//DrawDebugCamera(GetWorld(), Loc, Rot, 90, 2, FColor::Red, true);
}